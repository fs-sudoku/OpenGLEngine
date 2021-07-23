#include <render\mesh.h>

#include <GL\glew.h>
#include <GLM\glm.hpp>

#include <fstream>
#include <sstream>

#include <core\core.h>

constexpr auto vertex_obj_ptr       = "v ";
constexpr auto face_obj_ptr         = "f ";

constexpr auto attribute_v_coord    = -1;
constexpr auto attribute_v_normal   = -1;

// c style load obj function
inline void load_obj(const cstr& filename, std::vector<glm::vec4>& vertices, std::vector<glm::vec3>& normals, std::vector<ushort>& elements)
{
    using namespace std;

    ifstream in(filename, ios::in);
    if (in.fail()) {
        core->fatal_error(utils::format(
            "Cannot open OBJ Model. Path: ", filename.data())
        );
    }

    cstr line;
    while (getline(in, line))
    {
        if (line.substr(0, 2) == vertex_obj_ptr) {
            istringstream s(line.substr(2));
            glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
            vertices.push_back(v);
        }
        else if (line.substr(0, 2) == face_obj_ptr) {
            istringstream s(line.substr(2));
            ushort a, b, c;
            s >> a; s >> b; s >> c;
            a--; b--; c--;
            elements.push_back(a); elements.push_back(b); elements.push_back(c);
        }
    }

    normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (uint i = 0; i < elements.size(); i += 3) {

        ushort ia = elements[i];
        ushort ib = elements[i + 1];
        ushort ic = elements[i + 2];
        glm::vec3 normal = glm::normalize(glm::cross(
            glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
            glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
        normals[ia] = normals[ib] = normals[ic] = normal;
    }
}

Mesh::Mesh(const cstr& path) : filename(path)
{
    ::load_obj(path, vertices, normals, elements);
    core->print(utils::format(
        "Loaded model. Path: %s", path.data()), LogType::Sucess
    );
    this->bind();
}

Mesh::~Mesh()
{
    if (vbo_vertices != 0) {
        glDeleteBuffers(1, &vbo_vertices);
    }
    if (vbo_normals != 0) {
        glDeleteBuffers(1, &vbo_normals);
    }
    if (ibo_elements != 0) {
        glDeleteBuffers(1, &ibo_elements);
    }
    core->print(utils::format("Cleared mesh buffers in model: %s", filename.data()), LogType::Sucess);
}

void Mesh::draw()
{
    glBindVertexArray(vbo_vertices);
    glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}

void Mesh::bind()
{
    // create buffers/arrays
    glGenVertexArrays(1, &vbo_vertices);
    glGenBuffers(1, &vbo_vertices);
    glGenBuffers(1, &ibo_elements);

    glBindVertexArray(vbo_vertices);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(ushort), &elements[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), nullptr);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

    core->print(utils::format("Binded VBO and EBO in model: %s", filename.data()), LogType::Sucess);
}