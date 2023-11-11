#ifndef ACTIONS_H_
#define ACTIONS_H_

#include <vector>
#include <string>
#include <stdexcept>

#include <glibmm/ustring.h>

#include "aes.hpp"
#include "hash.hpp"


class ActionTransform {
public:
    enum Actions { AES128, AES256, MD5, actionmax };

    // Keep in same order as enum
    static constexpr const char *actionNames[] = {
        "AES_CTR_128",
        "AES_CTR_256",
        "MD5"
    };

    static Actions ustringToAction(const Glib::ustring &src);

    static std::vector<std::string> getInputLabels(const Actions action);
    static std::vector<std::pair<std::string, std::string>> transform(const std::vector<std::string> &input, const Actions action);
};

#endif