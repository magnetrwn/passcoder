#include "actions.hpp"

ActionTransform::Actions
ActionTransform::ustringToAction(const Glib::ustring &src) {
    for (uint i = 0; i < actionmax; i++)
        if (src == Glib::ustring(actionNames[i]))
            return static_cast<Actions>(i);
    throw std::runtime_error("Invalid action requested for ActionTransform::ustringToAction().");
}

std::vector<std::string>
ActionTransform::transform(const std::vector<std::string> &input, const Actions action) {
    std::vector<std::string> output;

    switch (action) {
        case AES128:
            output.reserve(1);
            output.push_back(AESTools::encCTR(input[0], input[1], input[2], AESTools::BitNumber::AES128));
            break;
        case AES256:
            output.reserve(1);
            output.push_back(AESTools::encCTR(input[0], input[1], input[2], AESTools::BitNumber::AES256));
            break;
        case MD5:
            //output.push_back(MD5Tools::md5(input[0]));
            break;
        default:
            throw std::runtime_error("Invalid action requested for ActionTransform::transform().");
    }

    return output;
}