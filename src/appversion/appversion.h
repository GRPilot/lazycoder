#ifndef APPVERSION_H
#define APPVERSION_H

struct AppInfo {

    inline static std::string name() { return "lazycoder"; }
    static QString qName();

    struct Version {
        static const unsigned short major{ 0 };
        static const unsigned short minor{ 2 };
        static const unsigned short patch{ 0 };

        static std::string str();
        static QString qStr();
    };

};

#endif // APPVERSION_H
