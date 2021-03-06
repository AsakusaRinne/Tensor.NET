using NUnit.Framework;
using Tensornet;

namespace TensorOpTest;

public class MatmulTest
{
    [SetUp]
    public void Setup()
    {
    }

    [Test]
    public void Test1()
    {
        var a = Tensor.FromArray<int>(new int[] { 1, 2, 3, 4, 5, 6 }, new TensorShape(2, 3));
        var b = Tensor.FromArray<int>(new int[] { -1, 1, 2, 1, -1, 3 }, new TensorShape(3, 2));
        var t = Tensor.FromArray<int>(new int[] { 0, 12, 0, 27 }, new TensorShape(2, 2));
        var p = a.Matmul(b);
        Assert.IsTrue(TensorUtils.IsValueEqual(t, p));
    }

    [Test]
    public void Test2()
    {
        var a = Tensor.FromArray<int>(new int[] { 1, 3, 5, 7, 9 }, new TensorShape(5, 1));
        var b = Tensor.FromArray<int>(new int[] { 2, 4, 6, 8, 10 }, new TensorShape(1, 5));
        var t = Tensor.FromArray<int>(new int[] { 2,  4,  6,  8,  10, 6,  12, 18, 24, 30, 10, 20, 30,
                    40, 50, 14, 28, 42, 56, 70, 18, 36, 54, 72, 90 }, new TensorShape(5, 5));
        var p = a.Matmul(b);
        Assert.IsTrue(TensorUtils.IsValueEqual(t, p));
    }

    [Test]
    public void Test3()
    {
        var a = Tensor.FromArray<double>(
            new double[] { -8.437620268739593,  7.740016490265845,   -2.718748159717318,
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
                            -15.76467722046241,  6.909490596651025,   4.4873495672112185 }, new TensorShape(1, 3, 4, 5));
        var b = Tensor.FromArray<double>(
            new double[] { -7.5827876234067375, -6.13534310952798,   -24.61466531083513,
                            -29.340869427040992, -20.037274582710047, -4.86314945103641,
                            -11.253241065283067, -21.142395003734165, -15.938173042067664,
                            0.9085878891952781,  0.280189916113617,   -20.26590286965132,
                            -28.689092469974103, 17.273583021966253,  -10.656336237819993,
                            18.449527456757245,  20.628373813727876,  27.511759771141662,
                            7.371968124588832,   14.434706651219557,  -20.905083235404213,
                            15.072039322092493,  -1.996775358994629,  -19.848550070097502,
                            16.3165181043086,    -25.318784739981893, 16.939771280984424,
                            0.4214739129998719,  1.7633298382284686,  17.659133993124158 }, new TensorShape(2, 1, 5, 3));
        var t = Tensor.FromArray<double>(
            new double[] { 204.6451028610454,   -245.47588653769554, 254.63190599885453,
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
                            -539.9063120367825,  -649.9585535562818,  135.97787257080606 }, new TensorShape(2, 3, 4, 3));
        var p = a.Matmul(b);
        Assert.IsTrue(TensorUtils.IsValueEqual(t, p));
    }

    [Test]
    public void Test4()
    {
        var a = Tensor.FromArray<double>(new double[] { 13.801236798018898, 0.20150833845125504, 4.106608693856746 }, new TensorShape(3));
        var b = Tensor.FromArray<double>(
            new double[] { -6.029940749041376, 20.753970138217923, -8.327858181118444,
                            -5.188661244672758, -9.050311859739129, 25.823909953964076,
                            24.2141803580204,   7.639806832295562,  22.544197020059514,
                            4.919069105496106,  2.2853523605274546, 24.35300450129494,
                            -22.79961732500386, 15.6879441785144,   -15.475480302585678,
                            -7.532337394669419, -21.94777113362987, -29.979519975059393,
                            27.491684686351228, 26.58821611324877,  7.474320930137196,
                            -20.15631608790095, -4.565966677821834, -3.5342800710705866 }, new TensorShape(2, 2, 3, 2));
        var t = Tensor.FromArray<double>(
            new double[] { -122.06486238579787, 391.4335909966807, 348.1135285464756,
                            206.4382766323594, -407.9122636772442, 91.88104632149431,
                            362.1747498694832, 348.3746955852936 }, new TensorShape(2, 2, 1, 2));
        var p = a.Matmul(b);
        Assert.IsTrue(TensorUtils.IsValueEqual(t, p));
    }

    [Test]
    public void Test5()
    {
        var a = Tensor.FromArray<double>(
            new double[] { -6.863911328798498,  6.285950807000905,  -4.551999714397429,
                            2.9442452537987336,  7.518547665868375,  12.767654916974834,
                            -16.77109517963331,  3.498415848555169,  -18.854288913388295,
                            13.669603055438088,  9.803970800255897,  -2.3831534529139695,
                            16.426462170858507,  0.8752655525789024, -3.34227609300401,
                            -10.513158897654233, -7.516722402630762, 9.963182036346243,
                            18.06872709287783,   9.18873334694911,   18.883364891458918,
                            -9.276501048623139,  -6.907303739816237, -18.57553847557326 }, new TensorShape(3, 1, 2, 4));
        var b = Tensor.FromArray<double>(new double[] { 7.893349570547649, 20.824402386134224,
                                                           12.672536168019768, 18.002556060079307 }, new TensorShape(4));
        var t = Tensor.FromArray<double>(
            new double[] { 72.04047666360029, 175.67342570179252, 217.1761421082951,
                           -83.73215691205462, 542.5424790165914, -466.06481963441973 }, new TensorShape(3, 1, 2, 1));
        var p = a.Matmul(b);
        Assert.IsTrue(TensorUtils.IsValueEqual(t, p));
    }

    [Test]
    public void Test6()
    {
        var a = Tensor.FromArray<double>(new double[] { 99.89 }, new TensorShape(1, 1));
        var b = Tensor.FromArray<float>(new float[] { 65.32f }, new TensorShape(1, 1, 1));
        var t = Tensor.FromArray<double>(new double[] { 6524.8148 }, new TensorShape(1, 1, 1));
        var p = a.Matmul(b);
        Assert.IsTrue(TensorUtils.IsValueEqual(t, p, 1e-4));
    }

    [Test]
    public void Test7()
    {
        var a = Tensor.FromArray<double>(new double[] { 99.89 }, new TensorShape(1, 1, 1, 1));
        var b = Tensor.FromArray<float>(new float[] { 65.32f }, new TensorShape(1));
        var t = Tensor.FromArray<double>(new double[] { 6524.8148 }, new TensorShape(1, 1, 1, 1));
        var p = a.Matmul(b);
        Assert.IsTrue(TensorUtils.IsValueEqual(t, p, 1e-4));
    }
}