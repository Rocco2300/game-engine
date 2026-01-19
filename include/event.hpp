#pragma once

#include <variant>

class Event {
public:
    struct KeyPress {
        int keycode;
    };

    struct KeyRelease {
        int keycode;
    };

    struct MouseMove {
        float xpos, ypos;
    };

    struct MouseButtonPress {
        int mouseButton;
    };

    struct MouseButtonRelease {
        int mouseButton;
    };

    template <typename T>
    Event(const T& eventSubType) {
        m_data = eventSubType;
    }

    template <typename T>
    Event& operator=(const T& eventSubType) {
        m_data = eventSubType;
        return *this;
    }

    template <typename T>
    bool is() const {
        return std::holds_alternative<T>(m_data);
    }

    template <typename T>
    T& get() {
        return std::get<T>(m_data);
    }

    template <typename T>
    const T& get() const {
        return std::get<T>(m_data);
    }

private:
    std::variant<KeyPress, KeyRelease, MouseMove, MouseButtonPress, MouseButtonRelease> m_data;
};