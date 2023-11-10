#ifndef ACTIONS_H_
#define ACTIONS_H_

#include <vector>
#include <string>
#include <stdexcept>

#include <glibmm/ustring.h>

#include "aes.hpp"

class ActionTransform {
public:
    enum Actions { AES128, AES256, MD5, actionmax };

    // Keep in the same order as the enum
    static constexpr const char *actionNames[] = {
        "AES Counter Mode (128-bit)",
        "AES Counter Mode (256-bit)",
        "MD5 Hash"
    };

    static Actions ustringToAction(const Glib::ustring &src);

    static std::vector<std::string> transform(const std::vector<std::string> &input, const Actions action);
};

#endif