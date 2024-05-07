#ifndef TURBINE_EDITOR_HPP
#define TURBINE_EDITOR_HPP

#include <turbine.hpp>

namespace Turbine {
class Editor : public App {
public:
    Editor();
    ~Editor();

    void run();

    App* create_app() {
        return new Editor();
    }
};
}

#endif