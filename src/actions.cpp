#include "actions.hpp"

ActionTransform::Actions
ActionTransform::ustringToAction(const Glib::ustring &src) {
    for (uint i = 0; i < actionmax; i++)
        if (src == Glib::ustring(actionNames[i]))
            return static_cast<Actions>(i);
    throw std::runtime_error("Invalid action requested for ActionTransform::ustringToAction().");
}

std::vector<std::pair<std::string, std::string>>
ActionTransform::transform(const std::vector<std::string> &input, const Actions action) {
    std::vector<std::pair<std::string, std::string>> output;
    std::string hexCiphertext;
    AESTools::BitNumber bits = AESTools::BitNumber::AES256;

    switch (action) {
        case AES128:
            bits = AESTools::BitNumber::AES128;
            [[fallthrough]];
        case AES256:
            output.reserve(1);
            hexCiphertext = AESTools::encCTR(input[0], input[1], input[2], bits);
            output.emplace_back(std::pair<std::string, std::string>("Hex Cipher", hexCiphertext));
            break;
        case MD5:
            output.reserve(1);
            hexCiphertext = HashTools::md5(input[0]);
            output.emplace_back(std::pair<std::string, std::string>("Hex Hash", hexCiphertext));
            break;
        default:
            throw std::runtime_error("Invalid action requested for ActionTransform::transform().");
    }

    return output;
}