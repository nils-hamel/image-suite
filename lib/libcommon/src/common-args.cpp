/*
 *  image-suite - common library
 *
 *      Nils Hamel - nils.hamel@bluewin.ch
 *      Copyright (c) 2016-2019 DHLAB, EPFL
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

    # include "common-args.hpp"

/*
    source - switches methods
 */

    bool lc_read_flag( int const argc, char ** argv, char const * const lc_long, char const * const lc_short ) {

        /* parsing arguments and parameters */
        for ( int lc_parse( 0 ); lc_parse < argc; lc_parse ++ ) {

            /* check argument short and long forms */
            if ( ( strcmp( argv[lc_parse], lc_long ) == 0 ) || ( strcmp( argv[lc_parse], lc_short ) == 0 ) ) {

                /* return answer */
                return( true );

            }

        }

        /* return answer */
        return( false );

    }

/*
    source - arguments and parameters methods
 */

    char * lc_read_string( int const argc, char ** argv, char const * const lc_long, char const * const lc_short ) {

        /* parsing arguments and parameters */
        for ( int lc_parse( 0 ); lc_parse < argc; lc_parse ++ ) {

            /* check argument short and long forms */
            if ( ( strcmp( argv[lc_parse], lc_long ) == 0 ) || ( strcmp( argv[lc_parse], lc_short ) == 0 ) ) {

                /* check consistency */
                if ( ( ++ lc_parse ) < argc ) {

                    /* return parameter */
                    return( argv[lc_parse] );

                /* return default value */
                } else { return( nullptr ); }

            }

        /* return default value */
        } return( nullptr );

    }

    intmax_t lc_read_signed( int const argc, char ** argv, char const * const lc_long, char const * const lc_short, intmax_t const lc_default ) {

        /* parsing arguments and parameters */
        for( int lc_parse( 0 ); lc_parse < argc; lc_parse ++ ) {

            /* check argument short and long forms */
            if ( ( strcmp( argv[lc_parse], lc_long ) == 0 ) || ( strcmp( argv[lc_parse], lc_short ) == 0 ) ) {

                /* check consistency */
                if ( ( ++ lc_parse ) < argc ) {

                    /* convert and return parameter */
                    return( strtoimax( argv[lc_parse], nullptr, 10 ) );

                /* return default value */
                } else { return( lc_default ); }

            }

        }

        /* Return default value */
        return( lc_default );

    }

    uintmax_t lc_read_unsigned( int const argc, char ** argv, char const * const lc_long, char const * const lc_short, uintmax_t const lc_default ) {

        /* parsing arguments and parameters */
        for( int lc_parse( 0 ); lc_parse < argc; lc_parse ++ ) {

            /* check argument short and long forms */
            if ( ( strcmp( argv[lc_parse], lc_long ) == 0 ) || ( strcmp( argv[lc_parse], lc_short ) == 0 ) ) {

                /* check consistency */
                if ( ( ++ lc_parse ) < argc ) {

                    /* convert and return parameter */
                    return( strtoumax( argv[lc_parse], nullptr, 10 ) );

                /* return default value */
                } else { return( lc_default ); }

            }

        }

        /* return default value */
        return( lc_default );

    }

    double lc_read_double( int const argc, char ** argv, char const * const lc_long, char const * const lc_short, double lc_default ) {

        /* parsing arguments and parameters */
        for( int lc_parse( 0 ); lc_parse < argc; lc_parse ++ ) {

            /* check argument short and long forms */
            if ( ( strcmp( argv[lc_parse], lc_long ) == 0 ) || ( strcmp( argv[lc_parse], lc_short ) == 0 ) ) {

                /* check consistency */
                if ( ( ++ lc_parse ) < argc ) {

                    /* convert and return parameter */
                    return( atof( argv[lc_parse] ) );

                /* return default value */
                } else { return( lc_default ); }

            }

        }

        /* return default value */
        return( lc_default );

    }

