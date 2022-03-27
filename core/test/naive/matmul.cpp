#include "core/test/common/matmul.h"

#include "core/base/include/tensor.h"
#include "core/op/naive/ops.h"
#include "core/test/common/checker.h"
#include "core/test/common/factory.h"
#include "core/test/common/utils.h"
#include "gtest/gtest.h"

using namespace nncore;
using namespace test;
using namespace opr;
using namespace opr::naive;

using F = NDArrayFactory;
using Param = param::matmul;

TEST(Naive, Matmul) {
  OpBase* oprs = OpNaiveImpl::get_instance();

  // Group 1
  Tensor a1 = F::from_list({1, 2, 3, 4, 5, 6}, {2, 3}, dtype::Int32());
  Tensor b1 = F::from_list({-1, 1, 2, 1, -1, 3}, {3, 2}, dtype::Int32());
  Tensor truth1 = F::from_list({0, 12, 0, 27}, {2, 2}, dtype::Int32());
  Param p1;

  Tensor pred1;
  ASSERT_TRUE(oprs->matmul(a1, b1, pred1, p1).is_ok());
  assert_same_data<int>(pred1, truth1, 0.0001f);

  // Group 2
  Tensor a2 = F::from_list({1, 3, 5, 7, 9}, {5, 1}, dtype::Int32());
  Tensor b2 = F::from_list({2, 4, 6, 8, 10}, {1, 5}, dtype::Int32());
  Tensor truth2 =
      F::from_list({2,  4,  6,  8,  10, 6,  12, 18, 24, 30, 10, 20, 30,
                    40, 50, 14, 28, 42, 56, 70, 18, 36, 54, 72, 90},
                   {5, 5}, dtype::Int32());
  Param p2;

  Tensor pred2;
  ASSERT_TRUE(oprs->matmul(a2, b2, pred2, p2).is_ok());
  assert_same_data<int>(pred2, truth2, 0.0001f);

  // Group 3
  Tensor a3 = F::from_list(
      {-7,  8,   -11, 11,  14,  6,   8,   9,   -7,  -17, 2,  -10, 10,  -12, 11,
       6,   -9,  13,  7,   -12, 17,  -8,  -2,  -18, -18, 19, -11, -18, -11, -11,
       -20, -4,  -6,  19,  -11, -18, -3,  6,   -19, 10,  -8, -17, -20, 9,   -3,
       -19, 1,   2,   14,  6,   11,  -8,  -14, 2,   0,   11, 9,   -2,  7,   4,
       -19, -4,  19,  5,   11,  -13, -6,  -16, 19,  -15, 11, -5,  -2,  10,  10,
       -6,  11,  13,  -5,  19,  8,   -12, 3,   8,   19,  4,  -20, 7,   13,  -15,
       -18, 7,   -2,  -11, 19,  -16, 8,   13,  -18, -1,  12, 14,  -14, -8,  14,
       12,  -16, 15,  -16, -15, -20, 4,   -19, -19, 3,   12, 1,   -13, -8,  16},
      {2, 3, 4, 5}, dtype::Int32());
  Tensor b3 = F::from_list(
      {-14, -8,  4,   16,  5,   2,   9,   -7,  -16, 1,   -16, -3,  8,   1,
       -1,  -3,  0,   -29, -28, 22,  11,  3,   -29, 3,   -21, -6,  4,   -22,
       14,  7,   17,  -17, 2,   -17, -10, -7,  0,   -3,  10,  -12, 15,  16,
       -9,  -26, 24,  -13, -23, 21,  -13, 3,   -27, -12, -2,  -30, 4,   -8,
       -7,  -16, -15, -30, -3,  -17, -9,  14,  25,  -22, -6,  0,   4,   -4,
       -29, -24, 0,   -12, 28,  -24, -7,  -21, 9,   -7,  -18, -2,  11,  2,
       24,  4,   8,   -28, -19, 20,  -15, -6,  -30, 18,  8,   27,  -13, -6,
       -13, 11,  18,  24,  -25, 0,   -14, 20,  -20, -28, -13, 0,   -8,  -29,
       -23, 21,  13,  5,   -29, -18, -25, -20, -9,  -6,  26,  27,  16,  20,
       3,   28,  -10, -10, -11, -4,  21,  28,  -6,  10,  26,  28,  28,  -6,
       17,  9,   21,  -16, -10, -12, -7,  21,  16,  15,  24,  -4,  13,  -30,
       18,  -6,  2,   14,  28,  0,   10,  15,  5,   -27, -7,  27,  -24, 14,
       -23, 11,  -13, 2,   -9,  -23, -24, -29, -30, 8,   0,   -29, 22,  -17,
       -13, -16, -14, -15, 21,  -1,  25,  16,  -8,  0,   -19, 28,  -2,  -24,
       15,  -22, 25,  27,  -20, 0,   10,  -19, 28,  -7,  -29, -30, -26, -6,
       4,   -26, -28, 14,  -22, 9,   -30, -16, -4,  -18, 18,  -2,  9,   -17,
       -5,  22,  23,  4,   28,  20,  20,  -6,  -2,  18,  11,  9,   0,   -16,
       -8,  2},
      {2, 3, 5, 8}, dtype::Int32());
  Tensor truth3 = F::from_list(
      {-233, 79,    56,   -718,  62,    -4,   575,   -363,  -99,  30,   -214,
       543,  95,    49,   -504,  284,   406,  -431,  -270,  469,  -128, -93,
       -356, 118,   -111, -272,  -48,   339,  199,   127,   -315, 49,   -77,
       892,  -303,  146,  484,   503,   -45,  951,   279,   933,  154,  442,
       565,  664,   -99,  576,   269,   -522, -44,   1012,  -301, 637,  -152,
       -851, -748,  -95,  547,   84,    -590, 88,    989,   116,  670,  -87,
       208,  -401,  -72,  -764,  303,   -436, -37,   452,   -452, -384, -806,
       -118, -456,  33,   108,   -58,   383,  -140,  226,   -436, 358,  -582,
       -533, 394,   -76,  -230,  -249,  86,   54,    -348,  798,  296,  245,
       -572, 37,    -92,  794,   -896,  -624, -88,   -1123, 258,  -332, -497,
       -303, -244,  -71,  -492,  395,   479,  217,   352,   541,  250,  579,
       -220, 464,   -503, 314,   496,   601,  -246,  -207,  424,  326,  -791,
       603,  151,   468,  925,   393,   -719, 583,   -4,    406,  987,  -186,
       119,  -488,  488,  -450,  113,   29,   -1207, 853,   90,   -463, 194,
       -560, 113,   -139, -1103, 142,   -691, -172,  216,   202,  -246, -532,
       -244, -1054, 80,   -164,  -766,  -537, -281,  606,   -418, -61,  -693,
       955,  -84,   -512, 569,   -1546, -194, -83,   1079,  132,  314,  168,
       92,   -150,  -460, -775,  -50},
      {2, 3, 4, 8}, dtype::Int32());
  Param p3;

  Tensor pred3;
  ASSERT_TRUE(oprs->matmul(a3, b3, pred3, p3).is_ok());
  assert_same_data<int>(pred3, truth3, 0.0001f);

  // Group 4
  Tensor a4 = F::from_list({1, 2, 5, -2, -4, 6, 1, 2, 5, -2, -4, 6,
                            1, 2, 5, -2, -4, 6, 1, 2, 5, -2, -4, 6},
                           {1, 4, 2, 3}, dtype::Int32());
  Tensor b4 = F::from_list({1, 1, 2, 3, -2, -4, 8, 15, -7, -1, 5, 0},
                           {1, 4, 3, 1}, dtype::Int32());
  Tensor truth4 = F::from_list({13, 6, -21, -22, 3, -118, 9, -18}, {1, 4, 2, 1},
                               dtype::Int32());
  Param p4;

  Tensor pred4;
  ASSERT_TRUE(oprs->matmul(a4, b4, pred4, p4).is_ok());
  assert_same_data<int>(pred4, truth4, 0.0001f);

  // Group 5
  Tensor a5 = F::from_list(
      {-8.437620268739593,  7.740016490265845,   -2.718748159717318,
       4.076362360501086,   -11.623399100527902, 15.142754042231019,
       -4.661652444132063,  19.803787411892657,  18.034918544512493,
       0.5484673220992633,  8.275595477083684,   -7.839590431114022,
       -6.525671288400314,  -6.6976349864874365, 11.678041249945768,
       8.027529844244178,   9.633496104375794,   19.21835118702979,
       1.855516944766265,   -4.416146677459146,  -1.6957639422062556,
       4.05269944529557,    -11.073620591053466, 5.481867755745512,
       -19.743764681683885, 10.823517335964155,  -13.170212197048649,
       -0.6085745188416105, -10.643371450680243, -2.9214692897250387,
       10.998063572711956,  -8.2473360940403,    -18.365489751487452,
       1.0113219544261298,  -14.207695003202518, -10.89741461633276,
       17.640823400385123,  -6.803936612665144,  -10.432236790357056,
       10.151183932088653,  11.632614090472163,  9.899002709432217,
       -16.0328862764357,   4.660828958932161,   11.278375899418531,
       -18.208043490908288, -8.304635778239406,  -1.5167989188120892,
       -10.563363578587627, -12.94383462875263,  -10.60842129295255,
       6.146827389030513,   -3.1127053415670645, -0.3788329301429343,
       5.065047819715378,   -19.485494518339422, -7.790652261044851,
       -15.76467722046241,  6.909490596651025,   4.4873495672112185},
      {1, 3, 4, 5}, dtype::Float64());
  Tensor b5 = F::from_list(
      {-7.5827876234067375, -6.13534310952798,   -24.61466531083513,
       -29.340869427040992, -20.037274582710047, -4.86314945103641,
       -11.253241065283067, -21.142395003734165, -15.938173042067664,
       0.9085878891952781,  0.280189916113617,   -20.26590286965132,
       -28.689092469974103, 17.273583021966253,  -10.656336237819993,
       18.449527456757245,  20.628373813727876,  27.511759771141662,
       7.371968124588832,   14.434706651219557,  -20.905083235404213,
       15.072039322092493,  -1.996775358994629,  -19.848550070097502,
       16.3165181043086,    -25.318784739981893, 16.939771280984424,
       0.4214739129998719,  1.7633298382284686,  17.659133993124158},
      {2, 1, 5, 3}, dtype::Float64());
  Tensor truth5 = F::from_list(
      {204.6451028610454,   -245.47588653769554, 254.63190599885453,
       -200.2528671581401,  -403.6714795350363,  -1037.0382604531853,
       -100.41452696082848, 444.1237337203991,   -50.28014887069747,
       -431.4138034439708,  -724.3654078010958,  -541.2932807875638,
       589.9744638696075,   -176.18769163944972, 297.82625554960487,
       385.34534307067946,  156.9094807871908,   54.160710580502084,
       773.7840651829667,   240.93324612115197,  193.01335037035483,
       -659.1048349134455,  29.6611816557244,    394.1328403132241,
       -517.5626502113245,  265.3783803432641,   -293.5803890561428,
       760.5509890823854,   83.63747341335062,   864.7565393290832,
       -210.53965883118147, 95.11606099496832,   234.54317446122678,
       431.2824832884677,   688.4052408516627,   580.9304146282878,
       -77.97495038431742,  -180.6052157399127,  -476.1827779964323,
       837.9928054550828,   -250.11800094461043, 436.1724309669594,
       -107.8276518256366,  260.74840560115484,  613.8562889468081,
       537.1959884794262,   211.51028931720717,  -408.54726433809026,
       -87.18820454463716,  -127.97879119314145, -167.37635674737132,
       -81.46814937971412,  298.7043152876581,   353.29081716454954,
       -124.1823264750605,  93.83775142666822,   605.7516461751454,
       -339.4930837885292,  325.461544706333,    -531.0002459790555,
       126.74511440221798,  316.74615601885375,  709.4434825820621,
       -597.8253632135093,  -247.82132339109492, -704.737830027385,
       -201.36741048315838, -105.36851711908248, -275.5465735989572,
       -539.9063120367825,  -649.9585535562818,  135.97787257080606},
      {2, 3, 4, 3}, dtype::Float64());
  Param p5;

  Tensor pred5;
  ASSERT_TRUE(oprs->matmul(a5, b5, pred5, p5).is_ok());
  assert_same_data<double>(pred5, truth5, 0.000001f);

  // Group 6
  Tensor a6 =
      F::from_list({13.801236798018898, 0.20150833845125504, 4.106608693856746},
                   {3}, dtype::Float64());
  Tensor b6 = F::from_list(
      {-6.029940749041376, 20.753970138217923, -8.327858181118444,
       -5.188661244672758, -9.050311859739129, 25.823909953964076,
       24.2141803580204,   7.639806832295562,  22.544197020059514,
       4.919069105496106,  2.2853523605274546, 24.35300450129494,
       -22.79961732500386, 15.6879441785144,   -15.475480302585678,
       -7.532337394669419, -21.94777113362987, -29.979519975059393,
       27.491684686351228, 26.58821611324877,  7.474320930137196,
       -20.15631608790095, -4.565966677821834, -3.5342800710705866},
      {2, 2, 3, 2}, dtype::Float64());
  Tensor truth6 =
      F::from_list({-122.06486238579787, 391.4335909966807, 348.1135285464756,
                    206.4382766323594, -407.9122636772442, 91.88104632149431,
                    362.1747498694832, 348.3746955852936},
                   {2, 2, 1, 2}, dtype::Float64());
  Param p6;

  Tensor pred6;
  ASSERT_TRUE(oprs->matmul(a6, b6, pred6, p6).is_ok());
  assert_same_data<double>(pred6, truth6, 0.000001);

  // Group 7
  Tensor a7 = F::from_list(
      {-6.863911328798498,  6.285950807000905,  -4.551999714397429,
       2.9442452537987336,  7.518547665868375,  12.767654916974834,
       -16.77109517963331,  3.498415848555169,  -18.854288913388295,
       13.669603055438088,  9.803970800255897,  -2.3831534529139695,
       16.426462170858507,  0.8752655525789024, -3.34227609300401,
       -10.513158897654233, -7.516722402630762, 9.963182036346243,
       18.06872709287783,   9.18873334694911,   18.883364891458918,
       -9.276501048623139,  -6.907303739816237, -18.57553847557326},
      {3, 1, 2, 4}, dtype::Float64());
  Tensor b7 = F::from_list({7.893349570547649, 20.824402386134224,
                            12.672536168019768, 18.002556060079307},
                           {4}, dtype::Float64());
  Tensor truth7 =
      F::from_list({72.04047666360029, 175.67342570179252, 217.1761421082951,
                    -83.73215691205462, 542.5424790165914, -466.06481963441973},
                   {3, 1, 2, 1}, dtype::Float64());
  Param p7;

  Tensor pred7;
  ASSERT_TRUE(oprs->matmul(a7, b7, pred7, p7).is_ok());
  assert_same_data<double>(pred7, truth7, 0.000001);

  // Group 8
  Tensor a8 = F::from_list(
      {17.466985062517146,  6.7664066410803585,  14.843100731907732,
       -4.6390678878805645, -11.721863661802509, -10.874290362288598,
       -17.450436421583543, -6.755345064323057,  8.327839373672429,
       5.832145729343814,   10.187632145963143,  -6.933134973938785,
       5.4345048380072605,  18.830019942772367,  -0.08915236388483905,
       -13.344241127102215, 19.56888266289109,   -2.325354778121529,
       -18.35114478739234,  16.080997940178044,  19.130843119578557,
       -7.780265244261599,  7.957347818762777,   -4.786855939893734},
      {3, 2, 4}, dtype::Float64());
  Tensor b8 =
      F::from_list({0.5741403351746364, -2.052231433802003, 25.24007024109701,
                    29.858219492503345, -18.67625475563329, 12.918972076270109,
                    -1.753392156743466, 23.42291952066134, 26.036713810702366,
                    -7.365878774868115, 20.185043802968643, -12.90536007406542},
                   {4, 3}, dtype::Float64());
  Tensor truth8 = F::from_list(
      {220.2063906086251, 91.81153535065636, 974.6173556521721,
       -251.06043201452295, -317.95010976837546, -803.5171742210955,
       212.12455323560656, -27.334838431359515, 640.2676444441263,
       663.7994184691494, -634.2694114728648, 550.3227877495598,
       -144.46959658080647, -101.97269754089359, -221.45579419121552,
       -200.01402938009352, 195.8067188946301, 651.3100820493304},
      {3, 2, 3}, dtype::Float64());
  Param p8;

  Tensor pred8;
  ASSERT_TRUE(oprs->matmul(a8, b8, pred8, p8).is_ok());
  assert_same_data<double>(pred8, truth8, 0.000001);

  // Group 9
  Tensor a9 = F::from_list({99.89}, {1}, dtype::Float32());
  Tensor b9 = F::from_list({65.32}, {1}, dtype::Float32());
  Tensor truth9 = F::from_list({6524.8148}, {1}, dtype::Float32());
  Param p9;

  Tensor pred9;
  ASSERT_TRUE(oprs->matmul(a9, b9, pred9, p9).is_ok());
  assert_same_data<float>(pred9, truth9, 0.000001);

  // Group 10
  Tensor a10 = F::from_list({99.89}, {1, 1}, dtype::Float32());
  Tensor b10 = F::from_list({65.32}, {1, 1, 1}, dtype::Float32());
  Tensor truth10 = F::from_list({6524.8148}, {1, 1, 1}, dtype::Float32());
  Param p10;

  Tensor pred10;
  ASSERT_TRUE(oprs->matmul(a10, b10, pred10, p10).is_ok());
  assert_same_data<float>(pred10, truth10, 0.000001);

  // Group 11
  Tensor a11 = F::from_list({99.89}, {1, 1, 1, 1}, dtype::Float32());
  Tensor b11 = F::from_list({65.32}, {1}, dtype::Float32());
  Tensor truth11 = F::from_list({6524.8148}, {1, 1, 1, 1}, dtype::Float32());
  Param p11;

  Tensor pred11;
  ASSERT_TRUE(oprs->matmul(a11, b11, pred11, p11).is_ok());
  assert_same_data<float>(pred11, truth11, 0.000001);
}