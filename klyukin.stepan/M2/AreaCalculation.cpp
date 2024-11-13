#include "AreaCalculation.hpp"
#include <system_error>
#include <vector>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>

klyukin::AreaCalculation::AreaCalculation(const std::unordered_set< std::string >& set, int threads, int tries, const std::unordered_map< std::string, klyukin::Circle >& circles)
{
  int pipe1_fds[2];
  int pipe2_fds[2];
  if (pipe(pipe1_fds) == -1) { // TODO RAII
    throw std::system_error(errno, std::system_category(), "pipe 1 creation failed");
  }
  if (pipe(pipe2_fds) == -1) {
    throw std::system_error(errno, std::system_category(), "pipe 2 creation failed");
  }

  pid_t p = fork();
  if (p < 0) {
    throw std::system_error(errno, std::system_category(), "fork failed");
  }
  // Parent process
  else if (p > 0) {
    close(pipe1_fds[0]); // Close reading end of first pipe
    close(pipe2_fds[1]); // Close writing end of second pipe

    for (auto circleName: set) {
      auto circle = circles.find(circleName)->second;
      const char* raw = reinterpret_cast< const char* >(&circle);
      size_t bytes = 0;
      while (bytes < sizeof(circle)) {
        int ret = write(pipe1_fds[1], raw + bytes, sizeof(circle) - bytes);
        if (ret < 0) {
          close(pipe1_fds[1]);
          throw std::system_error(errno, std::system_category(), "write to pipe 1 failed");
        } else {
          bytes += ret;
        }
      }
    }
    close(pipe1_fds[1]);
    resultFileDescriptor_ = pipe2_fds[0];
  } else {
    close(pipe1_fds[1]); // Close writing end of first pipe
    close(pipe2_fds[0]);

    std::vector< Circle > setCircles;
    const size_t bufferCirclesCount = 50;
    constexpr size_t bufferSize = bufferCirclesCount * sizeof(Circle);
    char buffer[bufferSize];
    size_t bytes = 0;
    while (true) {
      int ret = read(pipe1_fds[0], buffer + bytes, bufferSize - bytes);
      if (ret < 0) {
        close(pipe1_fds[0]);
        throw std::system_error(errno, std::system_category(), "read from pipe 1 failed");
      }
      bytes += ret;
      if (ret == 0 || bytes == bufferSize) {
        for (size_t i = 0; i < bytes; i += sizeof(Circle)) {
          setCircles.push_back(*(reinterpret_cast< Circle* >(buffer + i)));
        }
        if (ret == 0) {
          break;
        }
        bytes = 0;
      }
    }
    close(pipe1_fds[0]);

    // std::cout << "received " << threads << tries << ' ';
    // for (const Circle& circle: setCircles) {
    //   std::cout << circle << ' ';
    // }
    // std::cout << '\n';
    threads++;
    tries++;
    // const double area = calculateArea(setCircles.begin(), setCircles.end(), threads, tries);
    const double area = 1.1;
    const char* raw = reinterpret_cast< const char* >(&area);
    bytes = 0;
    while (bytes < sizeof(area)) {
      int ret = write(pipe2_fds[1], raw + bytes, sizeof(area) - bytes);
      if (ret < 0) {
        close(pipe2_fds[1]);
        throw std::system_error(errno, std::system_category(), "write to pipe 2 failed");
      } else {
        bytes += ret;
      }
    }
    close(pipe2_fds[1]);
    exit(0); // TODO separate main()
  }
}

double klyukin::AreaCalculation::requestCalculationResult()
{
  double res = 1;
  char* raw = reinterpret_cast< char* >(&res);
  size_t bytes = 0;
  while (bytes < sizeof(res)) {
    int ret = read(resultFileDescriptor_, raw + bytes, sizeof(res) - bytes);
    if (ret < 0) {
      // close(resultFileDescriptor_);
      throw std::system_error(errno, std::system_category(), "read from pipe 2 failed");
    } else {
      bytes += ret;
    }
  }
  // close(resultFileDescriptor_);
  return res;
}
