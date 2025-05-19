#ifndef DATA_HPP
#define DATA_HPP

#include "../utils/Vector2.hpp"
#include <string>
#include <vector>

class Data{
private:
    inline static const std::string DATA_PATH = "data/level_data.txt";
    std::vector<std::vector<Vector2>> exterior;
    std::vector<Vector2> origin;
    std::vector<f32> focal;
    std::vector<bool> isContinuous;

public:
    inline static const u8 N_FIGURES = 16;
    inline static const u8 N_BANDS_PER_FIGURE = 16;
    inline static const u8 N_CYCLES = 5;
    inline static const u8 N_LEVELS = 80;

    Data();
    Data(const Data& data) = default;
    ~Data() = default;

    inline const std::vector<std::vector<Vector2>>& getExterior() const{ return exterior; }
    inline const std::vector<Vector2>& getOrigin() const{ return origin; };
    inline const std::vector<f32>& getFocal() const{ return focal; };
    inline const std::vector<bool>& getIsContinuous() const{ return isContinuous; };
};

#endif
