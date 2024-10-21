/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** error_parser
*/

/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-nattan.cochet
** File description:
** error_parser
*/

#ifndef __ERROR_PARSER__
#define __ERROR_PARSER__

#include "utility.hpp"

/**
 * @brief Exception class for parsing errors.
 */
class errorParser : std::exception {
public:
    /**
     * @brief Enum representing different types of parsing errors.
     */
    enum typeOf {
        WRONG_NAME, /**< Incorrect name error. */
        WRONG_TYPE, /**< Incorrect type error. */
        UNKNOWN_ERROR /**< Unknown error. */
    };

    /**
     * @brief Constructs a parsing error with specified type and details.
     * @param error The type of parsing error.
     * @param details Additional details about the error.
     */
    errorParser(typeOf error, std::string details="");

    /**
     * @brief Destructor.
     */
    ~errorParser() = default;

    /**
     * @brief Returns a C-style character string describing the error.
     * @return A C-style character string describing the error.
     */
    const char* what() const noexcept override;

private:
    typeOf _type; /**< The type of parsing error. */
    std::string _message; /**< Additional details about the error. */
};

#endif /* !__ERROR_PARSER__ */
