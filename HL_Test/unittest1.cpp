#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HL_Test {
    const Setting setting = Setting::defaultSetting();
    TEST_CLASS(FourierTest) {
    public:
        TEST_METHOD(TestFFT) {
            ScalarField field(137, 87, 0.123, fockDarwin(setting, Orientation::Left));
            ScalarField field_FT = fourier::fft2d(field);
            ScalarField field_FT_IFT = fourier::ifft2d(field_FT);

            Assert::AreEqual(field.getWidth(), field_FT_IFT.getWidth());
            Assert::AreEqual(field.getHeight(), field_FT_IFT.getHeight());
            Assert::AreEqual(field.getGridSize(), field_FT_IFT.getGridSize());
        }

        TEST_METHOD(Convolution) {
            ScalarField img(138, 44, 0.123, fockDarwin(setting, Orientation::Left));
            ScalarField filter(24, 20, 0.123, gaussian(0.41));
            ScalarField conv = fourier::convolution(img, filter);

            Assert::AreEqual(conv.getWidth(), img.getWidth() - filter.getWidth());
            Assert::AreEqual(conv.getHeight(), img.getHeight() - filter.getHeight());
            Assert::AreEqual(conv.getGridSize(), img.getGridSize());
        }

        TEST_METHOD(C_AFC_Convert) {
            std::vector<Complex> vec(1337);
            std::vector<AFComplex> vec_AFC = fourier::convertCtoAFC(vec);
            std::vector<Complex> vec_AFC_AC = fourier::convertAFCtoC(vec_AFC);

            Assert::AreEqual(vec.size(), vec_AFC_AC.size());
            Assert::AreEqual(vec[337].real(), vec_AFC_AC[337].real());
        }
    };
    TEST_CLASS(HL) {
        TEST_METHOD(HL_calc) {
            
        }
    };
}
