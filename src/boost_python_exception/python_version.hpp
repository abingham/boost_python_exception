#ifndef INCLUDE_BOOST_PYTHON_EXCEPTION_PYTHON_VERSION_H
#define INCLUDE_BOOST_PYTHON_EXCEPTION_PYTHON_VERSION_H

namespace boost_python_exception {

	/**
	 * @brief The python version number this library was compiled with
	 */
	struct python_version{
		/**
		 * @brief Major part of version number
		 */
		unsigned int const major;

		/**
		 * @brief Minor part of version number
		 */
		unsigned int const minor;

		/**
		 * @brief Micro part of version number
		 */
		unsigned int const micro;

		/**
		 * @brief Get the python version this library was compiled with
		 */
		python_version();
	};

}

#endif /* INCLUDE_BOOST_PYTHON_EXCEPTION_PYTHON_VERSION_H */
