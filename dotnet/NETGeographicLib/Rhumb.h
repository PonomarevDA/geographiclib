#pragma once
/**
 * \file NETGeographicLib/Rhumb.h
 * \brief Header for NETGeographicLib::Rhumb and NETGeographicLib::RhumbLine classes
 *
 * NETGeographicLib is copyright (c) Scott Heiman (2013)
 * GeographicLib is Copyright (c) Charles Karney (2010-2012)
 * <charles@karney.com> and licensed under the MIT/X11 License.
 * For more information, see
 * http://geographiclib.sourceforge.net/
 **********************************************************************/

namespace NETGeographicLib {

  ref class RhumbLine;

  /**
   * \brief .NET wrapper for GeographicLib::Rhumb.
   *
   * This class allows .NET applications to access GeographicLib::Rhumb.
   *
   * Solve of the direct and inverse rhumb problems.
   *
   * The path of constant azimuth between two points on a ellipsoid at (\e
   * lat1, \e lon1) and (\e lat2, \e lon2) is called the rhumb line (also
   * called the loxodrome).  Its length is \e s12 and its azimuth is \e azi12
   * and \e azi2.  (The azimuth is the heading measured clockwise from north.)
   *
   * Given \e lat1, \e lon1, \e azi12, and \e s12, we can determine \e lat2,
   * and \e lon2.  This is the \e direct geodesic problem and its solution is
   * given by the function Rhumb::Direct.
   *
   * Given \e lat1, \e lon1, \e lat2, and \e lon2, we can determine \e azi12
   * and \e s12.  This is the \e inverse geodesic problem, whose solution is
   * given by Rhumb::Inverse.  This finds the shortest such rhumb line, i.e.,
   * the one that wraps no more than half way around the earth .
   *
   * Note that rhumb lines may be appreciably longer (up to 50%) than the
   * corresponding Geodesic.  For example the distance between London Heathrow
   * and Tokyo Narita via the rhumb line is 11400 km which is 18% longer than
   * the geodesic distance 9600 km.
   *
   * For more information on geodesics see \ref rhumb.
   *
   * C# Example:
   * \include example-Rhumb.cs
   * Managed C++ Example:
   * \include example-Rhumb.cpp
   * Visual Basic Example:
   * \include example-Rhumb.vb
   *
   * <B>INTERFACE DIFFERENCES:</B><BR>
   * The MajorRadius and Flattening functions are implemented as properties.
   **********************************************************************/

  public ref class Rhumb {
  private:
    // pointer to the unmanaged Rhumb object
    GeographicLib::Rhumb* m_pRhumb;

    // The finalizer destroys m_pRhumb when this object is destroyed.
    !Rhumb(void);
  public:

    /**
     * Constructor for a ellipsoid with
     *
     * @param[in] a equatorial radius (meters).
     * @param[in] f flattening of ellipsoid.  Setting \e f = 0 gives a sphere.
     *   Negative \e f gives a prolate ellipsoid.  If \e f &gt; 1, set
     *   flattening to 1/\e f.
     * @param[in] exact if true (the default) use an addition theorem for
     *   elliptic integrals to compute divided differences; otherwise use
     *   series expansion (accurate for |<i>f</i>| < 0.01).
     * @exception GeographicErr if \e a or (1 &minus; \e f) \e a is not
     *   positive.
     *
     * See \ref rhumb, for a detailed description of the \e exact parameter.
     **********************************************************************/
    Rhumb(double a, double f, bool exact);

    /**
    * \brief The destructor calls the finalizer.
    **********************************************************************/
    ~Rhumb() { this->!Rhumb(); }

    /**
     * Solve the direct rhumb problem.
     *
     * @param[in] lat1 latitude of point 1 (degrees).
     * @param[in] lon1 longitude of point 1 (degrees).
     * @param[in] azi12 azimuth of the rhumb line (degrees).
     * @param[in] s12 distance between point 1 and point 2 (meters); it can be
     *   negative.
     * @param[out] lat2 latitude of point 2 (degrees).
     * @param[out] lon2 longitude of point 2 (degrees).
     *
     * \e lat1 should be in the range [&minus;90&deg;, 90&deg;]; \e lon1 and \e
     * azi1 should be in the range [&minus;540&deg;, 540&deg;).  The values of
     * \e lon2 and \e azi2 returned are in the range [&minus;180&deg;,
     * 180&deg;).
     *
     * If point 1 is a pole, the cosine of its latitude is taken to be
     * 1/&epsilon;<sup>2</sup> (where &epsilon; is 2<sup>-52</sup>).  This
     * position, which is extremely close to the actual pole, allows the
     * calculation to be carried out in finite terms.  If \e s12 is large
     * enough that the rhumb line crosses a pole, the longitude of point 2
     * is indeterminate (a NaN is returned for \e lon2).
     **********************************************************************/
    void Direct(double lat1, double lon1, double azi12, double s12,
                [System::Runtime::InteropServices::Out] double% lat2, 
				[System::Runtime::InteropServices::Out] double% lon2);

    /**
     * Solve the inverse geodesic problem.
     *
     * @param[in] lat1 latitude of point 1 (degrees).
     * @param[in] lon1 longitude of point 1 (degrees).
     * @param[in] lat2 latitude of point 2 (degrees).
     * @param[in] lon2 longitude of point 2 (degrees).
     * @param[out] s12 rhumb distance between point 1 and point 2 (meters).
     * @param[out] azi12 azimuth of the rhumb line (degrees).
     *
     * The shortest rhumb line is found.  \e lat1 and \e lat2 should be in the
     * range [&minus;90&deg;, 90&deg;]; \e lon1 and \e lon2 should be in the
     * range [&minus;540&deg;, 540&deg;).  The value of \e azi12 returned is in
     * the range [&minus;180&deg;, 180&deg;).
     *
     * If either point is a pole, the cosine of its latitude is taken to be
     * 1/&epsilon;<sup>2</sup> (where &epsilon; is 2<sup>-52</sup>).  This
     * position, which is extremely close to the actual pole, allows the
     * calculation to be carried out in finite terms.
     **********************************************************************/
    void Inverse(double lat1, double lon1, double lat2, double lon2,
                 [System::Runtime::InteropServices::Out] double% s12, 
				 [System::Runtime::InteropServices::Out] double% azi12);

    /**
     * Set up to compute several points on a single geodesic.
     *
     * @param[in] lat1 latitude of point 1 (degrees).
     * @param[in] lon1 longitude of point 1 (degrees).
     * @param[in] azi12 azimuth of the rhumb line (degrees).
     * @return a RhumbLine object.
     *
     * \e lat1 should be in the range [&minus;90&deg;, 90&deg;]; \e lon1 and \e
     * azi12 should be in the range [&minus;540&deg;, 540&deg;).
     *
     * If point 1 is a pole, the cosine of its latitude is taken to be
     * 1/&epsilon;<sup>2</sup> (where &epsilon; is 2<sup>-52</sup>).  This
     * position, which is extremely close to the actual pole, allows the
     * calculation to be carried out in finite terms.
     **********************************************************************/
    RhumbLine^ Line(double lat1, double lon1, double azi12);

    /** \name Inspector functions.
     **********************************************************************/
    ///@{

    /**
     * @return the equatorial radius of the ellipsoid (meters).  This is
     *   the value used in the constructor.
     **********************************************************************/
	property double MajorRadius { double get(); }

    /**
     * @return f the  flattening of the ellipsoid.  This is the
     *   value used in the constructor.
     **********************************************************************/
	property double Flattening { double get(); }

    /**
     * A global instantiation of Rhumb with the parameters for the WGS84
     * ellipsoid.
     **********************************************************************/
    static Rhumb^ WGS84();
  };

  /**
   * \brief .NET wrapper for GeographicLib::RhumbLine.
   *
   * This class allows .NET applications to access GeographicLib::RhumbLine.
   *
   * Find a sequence of points on a single rhumb line.
   *
   * RhumbLine facilitates the determination of a series of points on a single
   * rhumb line.  The starting point (\e lat1, \e lon1) and the azimuth \e
   * azi12 are specified in the call to Rhumb::Line which returns a RhumbLine
   * object.  RhumbLine.Position returns the location of point 2 a distance \e
   * s12 along the rhumb line.

   * There is no public constructor for this class.  (Use Rhumb::Line to create
   * an instance.)  The Rhumb object used to create a RhumbLine must stay in
   * scope as long as the RhumbLine.
   *
   **********************************************************************/

  public ref class RhumbLine {
  private:
    // pointer to the unmanaged RhumbLine object.
    GeographicLib::RhumbLine* m_pRhumbLine;

    // The finalizer destroys m_pRhumbLine when this object is destroyed.
    !RhumbLine(void);
  public:
    /**
	 * \brief Constructor.
     *
     * For internal use only.  Developers should not call this constructor
     * directly.  Use the Rhumb::Line function to create RhumbLine objects.
     **********************************************************************/
	RhumbLine( GeographicLib::RhumbLine* pRhumbLine );

    /**
     * \brief The destructor calls the finalizer.
     **********************************************************************/
	~RhumbLine() { this->!RhumbLine(); }

    /**
     * Compute the position of point 2 which is a distance \e s12 (meters) from
     * point 1.
     *
     * @param[in] s12 distance between point 1 and point 2 (meters); it can be
     *   negative.
     * @param[out] lat2 latitude of point 2 (degrees).
     * @param[out] lon2 longitude of point 2 (degrees).
     *
     * The values of \e lon2 and \e azi2 returned are in the range
     * [&minus;180&deg;, 180&deg;).
     *
     * If \e s12 is large enough that the rhumb line crosses a pole, the
     * longitude of point 2 is indeterminate (a NaN is returned for \e lon2).
     **********************************************************************/
    void Position(double s12,  
                  [System::Runtime::InteropServices::Out] double% lat2,  
                  [System::Runtime::InteropServices::Out] double% lon2);

    /** \name Inspector functions
     **********************************************************************/
    ///@{

    /**
     * @return the latitude of point 1 (degrees).
     **********************************************************************/
    property double Latitude { double get(); }

    /**
     * @return the longitude of point 1 (degrees).
     **********************************************************************/
    property double Longitude { double get(); }

    /**
     * @return the azimuth of the rhumb line (degrees).
     **********************************************************************/
    property double Azimuth { double get(); }

    /**
     * @return the equatorial radius of the ellipsoid (meters).  This is
     *   the value inherited from the Geodesic object used in the constructor.
     **********************************************************************/
    property double MajorRadius { double get(); }

    /**
     * @return the flattening of the ellipsoid.  This is the value
     *   inherited from the Geodesic object used in the constructor.
     **********************************************************************/
    property double Flattening { double get(); }
  };

} // namespace NETGeographicLib

