//
// Created by sam on 2020-07-25.
//

#ifndef SDF_POLY_DATA_H
#define SDF_POLY_DATA_H


#include <iostream>
#include <vector>

// GLEW
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>

#include <Eigen/Dense>

typedef Eigen::Array<float, 1, 2> Arr2f;
typedef Eigen::Array<float, 1, 3> Arr3f;
typedef Eigen::Array<float, 1, 4> Arr4f;
typedef Eigen::Array<float, 1, Eigen::Dynamic> ArrXf;
typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatXf;

struct VertexField {
    VertexField()
            : pos(0), size(0), type(GL_FLOAT), normalize(false), offset(0) {}
    VertexField(GLuint in_pos, GLuint in_size, GLenum in_type, GLboolean in_normalize = GL_FALSE, int in_offset = 0)
            : pos(in_pos), size(in_size), type(in_type), normalize(in_normalize), offset(in_offset) {}

    GLuint pos;
    GLuint size;
    GLenum type;
    GLboolean normalize;
    int offset;
};
typedef std::vector<VertexField> VertexFieldVector;

class PolyData {
public:
    PolyData();
    PolyData(GLsizei size);
    ~PolyData() = default;

    void genCube();

    inline const float* data() const {return data_.data();}
    inline GLuint dataSize() const {return data_size_;}

    inline VertexFieldVector fields() const {return fields_;}
    inline GLuint fieldSize() const {return field_size_;}
protected:
    friend void bind(PolyData *poly_data_ptr);
    friend void erase(PolyData *poly_data_ptr);
    void bindVBO();
    GLuint calFieldSize() const;

private:
    GLuint *vbo_;
    GLsizei vbo_size_;
    MatXf data_;
    VertexFieldVector fields_;
    GLuint data_size_;
    GLuint field_size_;
};


#endif //SDF_POLY_DATA_H
