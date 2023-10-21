#include "Vwindow.hpp"

// std
#include <stdexcept>

namespace Visual {

VWindow::VWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
  initWindow();
}

VWindow::~VWindow() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void VWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto v_window = reinterpret_cast<VWindow*>(glfwGetWindowUserPointer(window));
    v_window->framebufferResized = true;
    v_window->width = width;
    v_window->height = height;
}

void VWindow::initWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
  glfwSetWindowUserPointer(window, this);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void VWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
  if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
    throw std::runtime_error("failed to craete window surface");
  }
}
}  // namespace V