//texture wowow

#ifndef TEXTURE_H
#define TEXTURE_H

class texture {
  public:
    virtual ~texture() = default;

    virtual vec3 value(double u, double v, const vec3& p) const = 0;
};

class solid_color : public texture {
  public:
    solid_color(const vec3& albedo) : albedo(albedo) {}

    solid_color(double red, double green, double blue) : solid_color(vec3(red,green,blue)) {}

    vec3 value(double u, double v, const vec3& p) const override {
        return albedo;
    }

  private:
    vec3 albedo;
};

#endif
