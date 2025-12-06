#include <gtest/gtest.h>
#include "studentai.h"


TEST(SkaiciavimoTestai, GalutnisVidurkis) {
    studentas s;
    s.setPaz({8, 10});
    s.setEgz(10);
    s.setSuma(18.0);
    s.setN(2.0);
    s.vidurkis();
    EXPECT_NEAR(s.gal_vid(), 9.6, 1e-6);
}

TEST(SKaiciavimoTestai, GalutinisMediana) {
    studentas s;
    s.setPaz({8, 10});
    s.setEgz(10);
    s.setSuma(18.0);
    s.setN(2.0);
    s.mediana();
    EXPECT_NEAR(s.gal_med(), 9.6, 1e-6);
}

TEST(StudentasTestai, DuomenuGavimas) {
    studentas s;
    s.setVar("Petras");
    s.setPav("Petraitis");
    s.setPaz({10,8});
    s.setEgz(10);
    s.setN(2.0);
    s.setSuma(18.0);
    
    s.vidurkis();
    s.mediana();

    EXPECT_EQ(s.vardas(), "Petras");
    EXPECT_EQ(s.pavarde(), "Petraitis");
    EXPECT_NEAR(s.gal_vid(), 9.6, 1e-6);
    EXPECT_NEAR(s.gal_med(), 9.6, 1e-6);
}

TEST(StudentasTestai, RuleOfThree) {
    studentas s1;
    s1.setVar("Jonas");
    s1.setPav("Jonaitis");
    s1.setPaz({10,8});
    s1.setEgz(10);
    s1.setN(2.0);
    s1.setSuma(18.0);
    
    s1.vidurkis();
    s1.mediana();
    
    studentas s2;
    s2 = s1;
    EXPECT_EQ(s1, s2);
    
    studentas s3(s1);
    EXPECT_EQ(s1, s3);
}

