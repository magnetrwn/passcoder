#ifndef CONVERT_H_
#define CONVERT_H_

#include <string>
#include <iomanip>
#include <sstream>
#include <codecvt>


class StringUtils {
public:
    inline static std::string toHex(const std::string &src) {
        std::stringstream hexStream;
        hexStream << std::hex << std::setfill('0');

        for (unsigned char c : src) {
            hexStream << std::setw(2) << static_cast<int>(c);
        }

        return hexStream.str();
    }
};

#endif
