/*
** EPITECH PROJECT, 2024
** test_libconfig
** File description:
** new_parser
*/

#ifndef NEW_PARSER_HPP_
#define NEW_PARSER_HPP_

#include <libconfig.h++>
#include "utility.hpp"
#include "hittable_list.hpp"
#include "primitives/cone.hpp"
#include "primitives/cylinder.hpp"
#include "primitives/quad.hpp"
#include "primitives/sphere.hpp"
#include "primitives/triangle.hpp"
#include "primitives/pyramide.hpp"
#include "error_parser.hpp"
#include "camera.hpp"

/**
 * @brief Base class representing a primitive shape.
 */
class IPrimitive {
public:
    double position_x; /**< X-coordinate of the position */
    double position_y; /**< Y-coordinate of the position */
    double position_z; /**< Z-coordinate of the position */
    double radius; /**< Radius of the shape */
    std::string material; /**< Material of the shape */
    double color_r; /**< Red component of the color */
    double color_g; /**< Green component of the color */
    double color_b; /**< Blue component of the color */
    double color_r2; /**< Secondary red component of the color */
    double color_g2; /**< Secondary green component of the color */
    double color_b2; /**< Secondary blue component of the color */
    double fuzz; /**< Fuzziness of the shape */
    double rotation_angle = 0; /**< Rotation angle */
    double translate_x = 0; /**< X-coordinate translation */
    double translate_y = 0; /**< Y-coordinate translation */
    double translate_z = 0; /**< Z-coordinate translation */
    std::string rotation_type = "y"; /**< Rotation type */
    std::string type; /**< Type of the shape */
};

/**
 * @brief Class representing a sphere primitive shape.
 */
class pSphere : public IPrimitive {
};

/**
 * @brief Class representing a cone primitive shape.
 */
class pCone : public IPrimitive {
public:
    std::string type; /**< Type of the cone */
    double _height; /**< Height of the cone */
};

/**
 * @brief Class representing a cylinder primitive shape.
 */
class pCyli : public IPrimitive {
public:
    std::string type; /**< Type of the cylinder */
    double base_x; /**< X-coordinate of the base */
    double base_y; /**< Y-coordinate of the base */
    double base_z; /**< Z-coordinate of the base */
};

/**
 * @brief Class representing a cube primitive shape.
 */
class pCube : public IPrimitive {
public:
    double top_x; /**< X-coordinate of the top */
    double top_y; /**< Y-coordinate of the top */
    double top_z; /**< Z-coordinate of the top */
};

/**
 * @brief Class representing a triangle primitive shape.
 */
class pTri : public IPrimitive {
public:
    double left_x; /**< X-coordinate of the left point */
    double left_y; /**< Y-coordinate of the left point */
    double left_z; /**< Z-coordinate of the left point */
    double right_x; /**< X-coordinate of the right point */
    double right_y; /**< Y-coordinate of the right point */
    double right_z; /**< Z-coordinate of the right point */
};

/**
 * @brief Class representing a pyramid primitive shape.
 */
class pPyra : public IPrimitive {
public:
    double basis_1_x; /**< X-coordinate of the first basis point */
    double basis_1_y; /**< Y-coordinate of the first basis point */
    double basis_1_z; /**< Z-coordinate of the first basis point */
    double basis_2_x; /**< X-coordinate of the second basis point */
    double basis_2_y; /**< Y-coordinate of the second basis point */
    double basis_2_z; /**< Z-coordinate of the second basis point */
    double basis_3_x; /**< X-coordinate of the third basis point */
    double basis_3_y; /**< Y-coordinate of the third basis point */
    double basis_3_z; /**< Z-coordinate of the third basis point */
    double basis_4_x; /**< X-coordinate of the fourth basis point */
    double basis_4_y; /**< Y-coordinate of the fourth basis point */
    double basis_4_z; /**< Z-coordinate of the fourth basis point */
};

/**
 * @brief Class representing a plane primitive shape.
 */
class pPlanes {
public:
    double position_x; /**< X-coordinate of the position */
    double position_y; /**< Y-coordinate of the position */
    double position_z; /**< Z-coordinate of the position */
    double dir_x; /**< X-coordinate of the direction */
    double dir_y; /**< Y-coordinate of the direction */
    double dir_z; /**< Z-coordinate of the direction */
    double axis_x; /**< X-coordinate of the axis */
    double axis_y; /**< Y-coordinate of the axis */
    double axis_z; /**< Z-coordinate of the axis */
    std::string material; /**< Material of the plane */
    std::string rotation_type = "y"; /**< Rotation type */
    double color_r; /**< Red component of the color */
    double color_g; /**< Green component of the color */
    double color_b; /**< Blue component of the color */
    double color_r2; /**< Secondary red component of the color */
    double color_g2; /**< Secondary green component of the color */
    double color_b2; /**< Secondary blue component of the color */
    double fuzz; /**< Fuzziness of the plane */
    double rotation_angle = 0; /**< Rotation angle */
    double translate_x = 0; /**< X-coordinate translation */
    double translate_y = 0; /**< Y-coordinate translation */
    double translate_z = 0; /**< Z-coordinate translation */
};

/**
 * @brief Class representing a point light source.
 */
class pPointLight {
public:
    pCyli _position_cylinder; /**< Position cylinder */
    pCone _position_cone; /**< Position cone */
    pSphere _position_sphere; /**< Position sphere */
    pPlanes _position_plane; /**< Position plane */
};

/**
 * @brief Class representing a collection of primitive shapes.
 */
class Primitives {
public:
    std::vector<pCyli> _cylinders; /**< Collection of cylinders */
    std::vector<pCone> _cone; /**< Collection of cones */
    std::vector<pSphere> _spheres; /**< Collection of spheres */
    std::vector<pPlanes> _planes; /**< Collection of planes */
    std::vector<pCube> _cubes; /**< Collection of cubes */
    std::vector<pTri> _triangles; /**< Collection of triangles */
    std::vector<pPyra> _pyramids; /**< Collection of pyramids */
};

/**
 * @brief Class for parsing a configuration file using libconfig.
 */
class newParser {
public:
    newParser(libconfig::Config &config);
    ~newParser() = default;

    /**
     * @brief Checks the validity of the parsed data.
     */
    void checkValidity(void);

    /**
     * @brief Parses the camera settings from the configuration.
     */
    void parseCamera(void);

    /**
     * @brief Parses the primitive shapes from the configuration.
     */
    void parsePrimitives(void);

    /**
     * @brief Parses the sphere shapes from the configuration.
     */
    void parseSpheres(void);

    /**
     * @brief Parses a cone shape from the configuration.
     * @param name Name of the cone shape
     */
    void parseCone(std::string name);

    /**
     * @brief Parses a cylinder shape from the configuration.
     * @param name Name of the cylinder shape
     */
    void parseCylinder(std::string name);

    /**
     * @brief Parses the cube shapes from the configuration.
     */
    void parseCubes(void);

    /**
     * @brief Parses the triangle shapes from the configuration.
     */
    void parseTriangles(void);

    /**
     * @brief Parses the plane shapes from the configuration.
     */
    void parsePlanes();

    /**
     * @brief Parses the pyramid shapes from the configuration.
     */
    void parsePyramids();

    /**
     * @brief Parses the light sources from the configuration.
     */
    void parseLights();

    /**
     * @brief Creates a shape object.
     * @param pos Position of the shape
     * @param radius Radius of the shape
     * @param material_ptr Pointer to the material of the shape
     * @param rotation Rotation of the shape
     * @param rotation_type Type of rotation
     * @param translation Translation of the shape
     * @return Shared pointer to the created shape
     */
    std::shared_ptr<hittable> createShape(point3 pos, double radius, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation);

    /**
     * @brief Creates a shape object with specified parameters.
     * @param shape Type of the shape
     * @param base Base position of the shape
     * @param top Top position of the shape
     * @param radius Radius of the shape
     * @param material_ptr Pointer to the material of the shape
     * @param rotation Rotation of the shape
     * @param rotation_type Type of rotation
     * @param translation Translation of the shape
     * @return Shared pointer to the created shape
     */
    std::shared_ptr<hittable> createShape(std::string shape, point3 base, point3 top, double radius, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation);

    /**
     * @brief Creates a shape object with specified parameters.
     * @param shape Type of the shape
     * @param pos Position of the shape
     * @param radius Radius of the shape
     * @param height Height of the shape
     * @param material_ptr Pointer to the material of the shape
     * @param rotation Rotation of the shape
     * @param rotation_type Type of rotation
     * @param translation Translation of the shape
     * @return Shared pointer to the created shape
     */
    std::shared_ptr<hittable> createShape(std::string shape, point3 pos, double radius, double height, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation);

    /**
     * @brief Creates a shape object with specified parameters.
     * @param pos Position of the shape
     * @param dir Direction of the shape
     * @param rot Rotation of the shape
     * @param material_ptr Pointer to the material of the shape
     * @param rotation Rotation of the shape
     * @param rotation_type Type of rotation
     * @param translation Translation of the shape
     * @return Shared pointer to the created shape
     */
    std::shared_ptr<hittable> createShape(point3 pos, point3 dir, vec3 rot, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation);

    /**
     * @brief Creates a shape object with specified parameters.
     * @param bot Bottom position of the shape
     * @param top Top position of the shape
     * @param material_ptr Pointer to the material of the shape
     * @param rotation Rotation of the shape
     * @param rotation_type Type of rotation
     * @param translation Translation of the shape
     * @return Shared pointer to the created shape
     */
    std::shared_ptr<hittable> createShape(point3 bot, point3 top, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation);

    /**
     * @brief Creates a shape object with specified parameters.
     * @param down Bottom position of the shape
     * @param left Left position of the shape
     * @param right Right position of the shape
     * @param material_ptr Pointer to the material of the shape
     * @param rotation Rotation of the shape
     * @param rotation_type Type of rotation
     * @param translation Translation of the shape
     * @return Shared pointer to the created shape
     */
    std::shared_ptr<hittable> createShape(point3 down, point3 left, point3 right, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation);

    /**
     * @brief Creates a shape object with specified parameters.
     * @param top Top position of the shape
     * @param basis1 First basis position of the shape
     * @param basis2 Second basis position of the shape
     * @param basis3 Third basis position of the shape
     * @param basis4 Fourth basis position of the shape
     * @param material_ptr Pointer to the material of the shape
     * @param rotation Rotation of the shape
     * @param rotation_type Type of rotation
     * @param translation Translation of the shape
     * @return Shared pointer to the created shape
     */
    std::shared_ptr<hittable> createShape(point3 top, point3 basis1, point3 basis2, point3 basis3, point3 basis4, std::shared_ptr<material> material_ptr, double rotation, std::string rotation_type, vec3 translation);

    /**
     * @brief Creates a Lambertian material.
     * @param colors Color of the material
     * @return Shared pointer to the created material
     */
    std::shared_ptr<lambertian> createMaterial(color colors);

    /**
     * @brief Creates a dielectric material.
     * @param refraction_index Refraction index of the material
     * @return Shared pointer to the created material
     */
    std::shared_ptr<dielectric> createMaterial(double refraction_index);

    /**
     * @brief Creates a metal material.
     * @param colors Color of the material
     * @param fuzz Fuzziness of the material
     * @return Shared pointer to the created material
     */
    std::shared_ptr<metal> createMaterial(color colors, double fuzz);

    /**
     * @brief Creates a diffuse light material
     * @param colors Color of the diffuse light
     * @return Shared pointer to the created material
    */
   std::shared_ptr<diffuse_light> createMaterial(color colors, char c);

    /**
     * @brief Creates a Lambertian texture.
     * @param scale Scale of the texture
     * @return Shared pointer to the created texture
     */
    std::shared_ptr<lambertian> createTexture(double scale);

    /**
     * @brief Creates a Lambertian texture with two colors.
     * @param color1 First color of the texture
     * @param color2 Second color of the texture
     * @param scale Scale of the texture
     * @return Shared pointer to the created texture
     */
    std::shared_ptr<lambertian> createTexture(color color1, color color2, double scale);

    /**
     * @brief Creates a material for a shape.
     * @param type Type of the shape
     * @param sphere Sphere data
     * @return Shared pointer to the created material
     */
    std::shared_ptr<material> createShapeMat(std::string type, pSphere sphere);

    /**
     * @brief Creates a material for a shape.
     * @param type Type of the shape
     * @param pyramid Pyramid data
     * @return Shared pointer to the created material
     */
    std::shared_ptr<material> createShapeMat(std::string type, pPyra pyramid);

    /**
     * @brief Creates a material for a shape.
     * @param type Type of the shape
     * @param cone Cone data
     * @return Shared pointer to the created material
     */
    std::shared_ptr<material> createShapeMat(std::string type, pCone cone);

    /**
     * @brief Creates a material for a shape.
     * @param type Type of the shape
     * @param cylinder Cylinder data
     * @return Shared pointer to the created material
     */
    std::shared_ptr<material> createShapeMat(std::string type, pCyli cylinder);

    /**
     * @brief Creates a material for a shape.
     * @param type Type of the shape
     * @param planes Plane data
     * @return Shared pointer to the created material
     */
    std::shared_ptr<material> createShapeMat(std::string type, pPlanes planes);

    /**
     * @brief Creates a material for a shape.
     * @param type Type of the shape
     * @param cube Cube data
     * @return Shared pointer to the created material
     */
    std::shared_ptr<material> createShapeMat(std::string type, pCube cube);

    /**
     * @brief Creates a material for a shape.
     * @param type Type of the shape
     * @param triangle Triangle data
     * @return Shared pointer to the created material
     */
    std::shared_ptr<material> createShapeMat(std::string type, pTri triangle);

    /**
     * @brief Parses a sphere light source from the configuration.
     * @param light Light configuration setting
     * @return Parsed point light source data
     */
    pPointLight parseLitSphere(const libconfig::Setting &light);

    /**
     * @brief Parses a cylinder light source from the configuration.
     * @param light Light configuration setting
     * @return Parsed point light source data
     */
    pPointLight parseLitCylinder(const libconfig::Setting &light);

    /**
     * @brief Parses a cone light source from the configuration.
     * @param light Light configuration setting
     * @return Parsed point light source data
     */
    pPointLight parseLitCone(const libconfig::Setting &light);

    /**
     * @brief Sets the primitive shapes data to the world object.
     * @param world Hittable list representing the world
     * @return Updated hittable list with primitive shapes
     */
    hittable_list setDataPrim(hittable_list world);

    /**
     * @brief Sets the light sources data to the lights object.
     * @param lights Hittable list representing the lights
     * @return Updated hittable list with light sources
     */
    hittable_list setDataLights(hittable_list lights);

    /**
     * @brief Sets the camera data.
     * @param cam Camera object
     * @return Updated camera object
     */
    camera setDataCam(camera cam);

    /**
     * @brief Get camera size.
     * @param element width or height
     * @return size_t
     */
    size_t getCameraSize(std::string element);

private:
    libconfig::Config &_cfg; /**< Reference to the libconfig configuration */
    libconfig::Setting &_root; /**< Reference to the root setting */
    std::vector<size_t> _cameraRes; /**< Camera resolution */
    std::vector<double> _cameraPos; /**< Camera position */
    std::vector<double> _cameraRot; /**< Camera rotation */
    std::vector<double> _BGColor; /**< Background color */
    std::vector<double> _cameraOrigin; /**< Camera origin */
    double _spp; /**< Samples per pixel */
    double _cameraDistance; /**< Camera distance */
    double _cameraFocus; /**< Camera focus */
    double _maxDepth; /**< Maximum depth */
    double _ambientScale = 0; /**< Ambient scale */
    float camera_fov; /**< Camera field of view */

    Primitives _primitives; /**< Collection of primitive shapes */

    std::vector <pPointLight> _lights; /**< Collection of light sources */
};

#endif /* !NEW_PARSER_HPP_ */
