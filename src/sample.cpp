#define PLUGIN_BUILD
#include "digital_twin/base.hpp"
#include "digital_twin/plugin.hpp"
#include <iostream>

class MyPlugin : public dt::IPlugin
{
public:
  std::string GetName() const override
  {
    return "My Sample Plugin";
  }

  std::string GetVersion() const override
  {
    return "1.0.0";
  }

  void Draw() const override
  {
    dt::log::event("Drawing My Sample Plugin UI");
  }

  void Work() const override
  {
    std::cout << "Working in My Sample Plugin" << std::endl;
  }
};

extern "C" PLUGIN_API dt::IPlugin *create_plugin()
{
  return new MyPlugin();
}

extern "C" PLUGIN_API void destroy_plugin(dt::IPlugin *p)
{
  delete p;
}