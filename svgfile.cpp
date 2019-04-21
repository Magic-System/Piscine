#include "svgfile.h"
#include <iostream>
#include <sstream>

const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" version=\"1.1\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

bool Svgfile::s_verbose = true;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{

    if (s_verbose)
        std::cout << "Opening SVG output file : "
                  << m_filename << std::endl;

    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    if (s_verbose)
        std::cout << "OK" << std::endl;

    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);

    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}

void Svgfile::addLinearGradient(std::string id, double x1, double y1, double x2, double y2, std::vector<Stop> stops)
{
    if(!m_gradientId[id])
    {
        m_gradientId[id] = true;
        m_ostrm << "<defs>" << std::endl
                << "<linearGradient "
                << attrib("id",id)
                << "x1=\"" << x1 << "%\" "
                << "y1=\"" << y1 << "%\" "
                << "x2=\"" << x2 << "%\" "
                << "y2=\"" << y2 << "%\""
                << ">" << std::endl;
        for(unsigned int i=0; i<stops.size(); i++)
        {
            m_ostrm << "<stop offset=\"" << stops[i].getOffset() << "%\" "
                    << "style=\"stop-color:" << stops[i].getColor()
                    << ";stop-opacity:" << stops[i].getOpacity()
                    << "\" />" << std::endl;
        }
        m_ostrm << "</linearGradient>" << std::endl
                << "</defs>" << std::endl;
    }
}

void Svgfile::addRadialGradient(std::string id, double cx, double cy, double r, double fx, double fy, std::vector<Stop> stops)
{
    if(!m_gradientId[id])
    {
        m_gradientId[id] = true;
        m_ostrm << "<defs>" << std::endl
                << "<radialGradient "
                << attrib("id",id)
                << "cx=\"" << cx << "%\" "
                << "cy=\"" << cy << "%\" "
                << "r=\"" << r << "%\" "
                << "fx=\"" << fx << "%\" "
                << "fy=\"" << fy << "%\""
                << ">" << std::endl;
        for(unsigned int i=0; i<stops.size(); i++)
        {
            m_ostrm << "<stop offset=\"" << stops[i].getOffset() << "%\" "
                    << "style=\"stop-color:" << stops[i].getColor()
                    << ";stop-opacity:" << stops[i].getOpacity()
                    << "\" />" << std::endl;
        }
        m_ostrm << "</radialGradient>" << std::endl
                << "</defs>" << std::endl;
    }
}

void Svgfile::addDisk(double x, double y, double r, std::string color, std::string id)
{
    m_ostrm << "<circle "
            << attrib("id", id)
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r);
    if(m_gradientId[color])
        m_ostrm << "fill=\"url(#" << color << ")\" ";
    else
        m_ostrm << attrib("fill", color);
    m_ostrm << "/>\n";
}

void Svgfile::addCircle(double x, double y, double r, double ep, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", "none")
            << attrib("stroke", color )
            << attrib("stroke-width", ep )
            << "/>\n";
}

void Svgfile::addEllipse(double x, double y, double rx, double ry,
                         std::string colorFill, double thickness, std::string colorStroke)
{
    m_ostrm << "<ellipse "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("rx",  rx)
            << attrib("ry",  ry);
    if(m_gradientId[colorFill])
        m_ostrm << "fill=\"url(#" << colorFill << ")\" ";
    else
        m_ostrm << attrib("fill", colorFill);
    m_ostrm << attrib("stroke", colorStroke)
            << attrib("stroke-width", thickness)
            << "/>\n";
}

void Svgfile::addEllipse(double x, double y, double rx, double ry, std::string colorFill)
{
    m_ostrm << "<ellipse "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("rx",  rx)
            << attrib("ry",  ry);
    if(m_gradientId[colorFill])
        m_ostrm << "fill=\"url(#" << colorFill << ")\" ";
    else
        m_ostrm << attrib("fill", colorFill);
    m_ostrm << "/>\n";
}

/// <polygon points="200,10 250,190 160,210" style="fill:lime;stroke:purple;stroke-width:1" />
void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke)
{

    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3;
    if(m_gradientId[colorFill])
        m_ostrm << "\" style=\"fill:url(#" << colorFill << ")";
    else
        m_ostrm << "\" style=\"fill:" << colorFill;
    m_ostrm << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}


void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3;
    if(m_gradientId[colorFill])
        m_ostrm << "\" style=\"fill:url(#" << colorFill << ")";
    else
        m_ostrm << "\" style=\"fill:" << colorFill;
    m_ostrm << "\" />\n";
}

void Svgfile::addRectangle(double x, double y, double rx, double ry, double width, double height,
                           std::string colorFill, double thickness, std::string colorStroke)
{
    m_ostrm << "<rect x=\"" << x << "\" y=\"" << y
            << "\" rx=\"" << rx << "\" ry=\"" << ry
            << "\" width=\"" << width << "\" height=\"" << height;
    if(m_gradientId[colorFill])
        m_ostrm << "\" style=\"fill:url(#" << colorFill << ")";
    else
        m_ostrm << "\" style=\"fill:" << colorFill;
    m_ostrm << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}

void Svgfile::addRectangle(double x, double y, double rx, double ry, double width, double height, std::string colorFill)
{
    m_ostrm << "<rect x=\"" << x << "\" y=\"" << y
            << "\" rx=\"" << rx << "\" ry=\"" << ry
            << "\" width=\"" << width << "\" height=\"" << height;
    if(m_gradientId[colorFill])
        m_ostrm << "\" style=\"fill:url(#" << colorFill << ")";
    else
        m_ostrm << "\" style=\"fill:" << colorFill;
    m_ostrm << "\" />\n";
}

void Svgfile::addPolygone(std::vector<double> x, std::vector<double> y,
                          std::string colorFill, double thickness, std::string colorStroke)
{
    m_ostrm << "<polygon points=\"";
    for(unsigned int i=0; i<x.size(); i++)
    {
        m_ostrm << x[i] << " " << y[i] << " ";
    }
    if(m_gradientId[colorFill])
        m_ostrm << "\" style=\"fill:url(#" << colorFill << ")";
    else
        m_ostrm << "\" style=\"fill:" << colorFill;
    m_ostrm << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}

void Svgfile::addPolygone(std::vector<double> x, std::vector<double> y, std::string colorFill)
{
    m_ostrm << "<polygon points=\"";
    for(unsigned int i=0; i<x.size(); i++)
    {
        m_ostrm << x[i] << " " << y[i] << " ";
    }
    if(m_gradientId[colorFill])
        m_ostrm << "\" style=\"fill:url(#" << colorFill << ")";
    else
        m_ostrm << "\" style=\"fill:" << colorFill;
    m_ostrm << "\" />\n";
}

void Svgfile::addPath(std::string path, std::string colorFill, double thickness, std::string colorStroke)
{
    m_ostrm << "<path d=\"" << path;
    if(m_gradientId[colorFill])
        m_ostrm << "\" style=\"fill:url(#" << colorFill << ")";
    else
        m_ostrm << "\" style=\"fill:" << colorFill;
    m_ostrm << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}

void Svgfile::addPath(std::string path, std::string colorFill)
{
    m_ostrm << "<path d=\"" << path;
    if(m_gradientId[colorFill])
        m_ostrm << "\" style=\"fill:url(#" << colorFill << ")";
    else
        m_ostrm << "\" style=\"fill:" << colorFill;
    m_ostrm << "\" />\n";
}

void Svgfile::addLine(double x1, double y1, double x2, double y2, std::string color, std::string id, int opacity)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2);
    if(m_gradientId[color])
        m_ostrm << "stroke=\"url(#" << color << ")\" ";
    else
        m_ostrm << attrib("stroke", color);
    m_ostrm << "/>\n";
}

void Svgfile::addLine(double x1, double y1, double x2, double y2, double thickness, std::string color, std::string id, int opacity)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke-width", thickness);
    if(m_gradientId[color])
        m_ostrm << "stroke=\"url(#" << color << ")\" ";
    else
        m_ostrm << attrib("stroke", color);
    m_ostrm << "/>\n";
}

void Svgfile::addCross(double x, double y, double span, std::string color)
{
    addLine(x-span, y-span, x+span, y+span, color);
    addLine(x-span, y+span, x+span, y-span, color);
}

void Svgfile::addText(double x, double y, std::string text, std::string color, int opacity)
{
    /// <text x="180" y="60">Un texte</text>
    m_ostrm << "<text "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("fill", color)
            << ">" << text << "</text>\n";
}

void Svgfile::addText(double x, double y, double val, std::string color, int opacity)
{
    std::ostringstream oss;
    oss << val;
    addText(x, y, oss.str(), color);
}

void Svgfile::addGrid(double span, bool numbering, std::string color)
{
    double y=0;
    while (y<=m_height)
    {
        addLine(0, y, m_width, y, color);
        if (numbering)
            addText(5, y-5, y, color);
        y+=span;
    }

    double x=0;
    while (x<=m_width)
    {
        addLine(x, 0, x, m_height, color);
        if (numbering)
            addText(x+5, 15, x, color);
        x+=span;
    }
}

void Svgfile::addAnimationOpacite(std::string idObj, std::string idBegin)
{
    m_ostrm << "<animate attributName=\"opacity\" from=\"o\" to=\"1\" dur=\"2s\" "
            << "xlink:href=\"#" << idObj << "\""
            << "begin=\"" << idBegin << ".mouseover\" />";
}

std::string Svgfile::makeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}
