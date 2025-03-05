#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include "uc_apng_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace cv;
using namespace std;

int main( int argc, const char** argv )
{
    std::string filename = argc > 1 ? argv[1] : "C:/images/apng/chesster_death_animation.apng";

    //! [init_animation]
    Animation animation;
    //! [init_animation]

    //! [read_animation]
    bool success = imreadanimation(filename, animation);
    if (!success) {
        std::cerr << "Failed to load animation frames\n";
        return -1;
    }
    //! [read_animation]
    {
        auto loader = uc::apng::create_file_loader(filename);

        std::cout << "\n\"" << filename << "\" ("
            << loader.width() << "x" << loader.height() << "), "
            << loader.num_frames() << "frames, "
            << loader.num_plays() << " times to loop (0 indicates infinite looping).\n";
        int i = 0;
        while (loader.has_frame()) {
            auto frame = loader.next_frame();

            std::ostringstream os;
            os << "out" << std::setw(3) << std::setfill('0') << frame.index << ".png";
            auto outputfile = os.str();

            std::cout << " " << frame.index << " / " << loader.num_frames() << " : \"" << outputfile << "\" "
                << "(" << frame.image.width() << "x" << frame.image.height() << ")"
                << " delay=" << frame.delay_num << "/" << frame.delay_den
                << " " << (frame.is_default ? "default " : " ") << "\n";
            imshow("Animation", animation.frames[i]);
            Mat img(frame.image.height(), frame.image.width(), CV_8UC4, frame.image.data());
            //cvtColor(img, img, COLOR_RGBA2BGRA);
            imshow("uc", img);
            waitKey();
            i++;
            //stbi_write_png(outputfile.c_str(), frame.image.width(), frame.image.height(), 4, frame.image.data(), frame.image.width() * 4);
        }
    }

    return 0;
}
