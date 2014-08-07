#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_PYTHON_VERSION_H
#define INCLUDE_BOOST_PYTHON_EXCEPTION_PYTHON_VERSION_H

#include <iosfwd>

namespace boost_python_exception {

	/**
	 * @brief A python version number
	 */
	struct version{
		/**
		 * @brief Major part of version number
		 */
		unsigned int major;

		/**
		 * @brief Minor part of version number
		 */
		unsigned int minor;

		/**
		 * @brief Micro part of version number
		 */
		unsigned int micro;

		/**
		 * @brief Construct a new version object
		 * @param major Major version (first number)
		 * @param minor Minor version (second number)
		 * @param micro Micro version (third number)
		 */
		version(unsigned int major, unsigned int minor, unsigned int micro);
	};

	/**
	 * @brief Compares two versions numbers for identity
	 * @param lhs left hand side argument
	 * @param rhs right hand side argument
	 * @return true if both arguments are in equal major, minor and micro version
	 */
	bool operator== (version const& lhs, version const& rhs);

	/**
	 * @brief Compares two versions numbers for identity
	 * @param lhs left hand side argument
	 * @param rhs right hand side argument
	 * @return false if both arguments are in equal major, minor and micro version
	 */
	bool operator!= (version const& lhs, version const& rhs);

	/**
	 * @brief Inserts a boost_python_exception::version into an output stream
	 * @param lhs Stream the version is inserted into
	 * @param rhs Version to insert in stream
	 * @return Stream passed as left hand argument to allow for chaining
	 */
	std::ostream& operator<< (std::ostream& lhs, version const& rhs);

	/**
	 * @brief Returns the python version used to <i>build</i> boost_python_exception
	 * @return A version string which includes the python version
	 *
	 * The following code extracts the version from the python headers:
	 * \code
	 * #include <patchlevel.h> // python header
	 *
	 * version python_version()
	 * {
	 *     return {PY_MAJOR_VERSION, PY_MINOR_VERSION, PY_MICRO_VERSION};
	 * }
	 * \endcode
	 *
	 */
	version python_version() throw();

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_PYTHON_VERSION_H */
