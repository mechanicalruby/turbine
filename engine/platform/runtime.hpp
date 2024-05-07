#ifndef TURBINE_RUNTIME_HPP
#define TURBINE_RUNTIME_HPP

namespace Turbine {
class Runtime {
public:
    Runtime() = default;

private:
    std::unique_ptr<Renderer> renderer;
};
}

#endif