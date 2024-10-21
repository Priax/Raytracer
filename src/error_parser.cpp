/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** error_parser
*/

#include "new_parser.hpp"

const char *errorParser::what() const noexcept
{
    return _message.c_str();
}

errorParser::errorParser(typeOf error, std::string details)
{
    _type = error;

    switch (this->_type) {
        case WRONG_NAME:
            _message = "Invalid provided section names";
            break;
        case WRONG_TYPE:
            _message = "Illegal type used for variable";
            break;
        default:
            _message = "Unknown error";
            break;
    }
    if (!details.empty())
        _message += ": " + details;
}
