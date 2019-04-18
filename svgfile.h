#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <map>

constexpr char defcol[] = "black";

class Stop
{
public:
    Stop() = default;
    Stop(double offset, std::string color, double opacity = 1)
    : m_offset(offset), m_color(color), m_opacity(opacity){};
    ~Stop() = default;

    double getOffset() const { return m_offset; };
    std::string getColor() const { return m_color; };
    double getOpacity() const { return m_opacity; };
private:
    double m_offset;
    std::string m_color;
    double m_opacity;
};

class Svgfile
{
    public:
        Svgfile(std::string _filename = "output.svg", int _width=1000, int _height=800);
        ~Svgfile();

        void addLinearGradient(std::string id, double x1, double y1, double x2, double y2, std::vector<Stop> stops);
        void addRadialGradient(std::string id, double cx, double cy, double r, double fx, double fy, std::vector<Stop> stops);
        void addDisk(double x, double y, double r, std::string color=defcol);
        void addCircle(double x, double y, double r, double ep, std::string color=defcol);
        void addEllipse(double cx, double cy, double rx, double ry,
                        std::string colorFill, double thickness, std::string colorStroke);
        void addEllipse(double cx, double cy, double rx, double ry,
                        std::string colorFill=defcol);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);
        void addRectangle(double x, double y, double rx, double ry, double width, double height,
                          std::string colorFill, double thickness, std::string colorStroke);
        void addRectangle(double x, double y, double rx, double ry, double width, double height,
                          std::string colorFill=defcol);
        void addPolygone(std::vector<double> x, std::vector<double> y,
                         std::string colorFill, double thickness, std::string colorStroke);
        void addPolygone(std::vector<double> x, std::vector<double> y, std::string colorFill=defcol);
        void addPath(std::string path, std::string colorFill, double thickness, std::string colorStroke);
        void addPath(std::string path, std::string colorFill=defcol);
        void addLine(double x1, double y1, double x2, double y2, std::string color=defcol);
        void addLine(double x1, double y1, double x2, double y2, double thickness, std::string color);
        void addCross(double x, double y, double span, std::string color=defcol);

        void addText(double x, double y, std::string text, std::string color=defcol);
        void addText(double x, double y, double val, std::string color=defcol);

        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");

        static std::string makeRGB(int r, int g, int b);

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

        static bool s_verbose;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        std::map<std::string, bool> m_gradientId;

        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;
};

#endif // SVGFILE_H_INCLUDED
