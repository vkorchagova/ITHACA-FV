#include "ITHACAparameters.H"

ITHACAparameters* ITHACAparameters::instance = nullptr;

ITHACAparameters::ITHACAparameters(fvMesh& mesh, Time& localTime)
    :
    runTime(localTime),
    mesh(mesh)
{
    ITHACAdict = new IOdictionary
    (
        IOobject
        (
            "ITHACAdict",
            runTime.system(),
            runTime,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE,
            true
        )
    );
    precision = ITHACAdict->lookupOrDefault<label>("OutPrecision", 10);
    word typeout = ITHACAdict->lookupOrDefault<word>("OutType", "scientific");

    if (typeout == "fixed")
    {
        outtype = std::ios_base::fixed;
    }
    else if (typeout == "scientific")
    {
        outtype = std::ios_base::scientific;
    }
    else
    {
        outtype = std::ios_base::scientific;
        WarningInFunction
            << "Unknown OutType " << outtype << nl
            << "    Available types: fixed, scientific." << nl
            << "    Default OutType scientific is used." 
            << endl;
    }

    eigensolver = ITHACAdict->lookupOrDefault<word>("EigenSolver", "spectra");
    exportPython = ITHACAdict->lookupOrDefault<bool>("exportPython", 0);
    exportMatlab = ITHACAdict->lookupOrDefault<bool>("exportMatlab", 0);
    exportTxt = ITHACAdict->lookupOrDefault<bool>("exportTxt", 0);
    debug = ITHACAdict->lookupOrDefault<bool>("debug", 0);
    warnings = ITHACAdict->lookupOrDefault<bool>("warnings", 0);
}

ITHACAparameters* ITHACAparameters::getInstance(fvMesh& mesh,
        Time& localTime)
{
    if (instance == nullptr)
    {
        instance = new ITHACAparameters(mesh, localTime);
    }

    return instance;
}

ITHACAparameters* ITHACAparameters::getInstance()
{
    M_Assert(instance != nullptr,
             "ITHACAparameters needs to be initialized, call ITHACAparameters::getInstance(mesh, runTime) first");
    return instance;
}
