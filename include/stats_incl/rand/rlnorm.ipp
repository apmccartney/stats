/*################################################################################
  ##
  ##   Copyright (C) 2011-2018 Keith O'Hara
  ##
  ##   This file is part of the StatsLib C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

/* 
 * Sample from a log-normal distribution
 */

//
// single draw

namespace internal
{

template<typename T>
statslib_inline
T
rlnorm_compute(const T mu_par, const T sigma_par, rand_engine_t& engine)
{
    return( !lnorm_sanity_check(mu_par,sigma_par) ? \
                STLIM<T>::quiet_NaN() :
            //
            stmath::exp(rnorm(mu_par,sigma_par,engine)) );
}

template<typename T1, typename T2, typename TC = common_return_t<T1,T2>>
statslib_inline
TC
rlnorm_type_check(const T1 mu_par, const T2 sigma_par, rand_engine_t& engine)
{
    return rlnorm_compute(static_cast<TC>(mu_par),static_cast<TC>(sigma_par),engine);
}

}

/**
 * Random sampling function for the Log-Normal distribution
 *
 * @param mu_par the location parameter, a real-valued input.
 * @param sigma_par the scale parameter, a real-valued input.
 * @param engine a random engine, passed by reference.
 *
 * @return a pseudo-random draw from the Log-Normal distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rand_engine_t engine(1776);
 * stats::rlnorm(1.0,2.0,engine);
 * \endcode
 */

template<typename T1, typename T2>
statslib_inline
common_return_t<T1,T2>
rlnorm(const T1 mu_par, const T2 sigma_par, rand_engine_t& engine)
{
    return internal::rlnorm_type_check(mu_par,sigma_par,engine);
}

/**
 * Random sampling function for the Log-Normal distribution
 *
 * @param mu_par the location parameter, a real-valued input.
 * @param sigma_par the scale parameter, a real-valued input.
 * @param seed_val initialize the random engine with a non-negative integral-valued seed.
 *
 * @return a pseudo-random draw from the Log-Normal distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rlnorm(1.0,2.0,1776);
 * \endcode
 */

template<typename T1, typename T2>
statslib_inline
common_return_t<T1,T2>
rlnorm(const T1 mu_par, const T2 sigma_par, const ullint_t seed_val)
{
    rand_engine_t engine(seed_val);
    return rlnorm(mu_par,sigma_par,engine);
}

//
// vector/matrix output

namespace internal
{

template<typename T1, typename T2, typename rT>
statslib_inline
void
rlnorm_vec(const T1 mu_par, const T2 sigma_par, rT* __stats_pointer_settings__ vals_out, const ullint_t num_elem)
{
    RAND_DIST_FN_VEC(rlnorm,vals_out,num_elem,mu_par,sigma_par);
}

}

/**
 * @brief Random matrix sampling function for the Log-Normal distribution
 *
 * @param n the number of output rows
 * @param k the number of output columns
 * @param mu_par the location parameter, a real-valued input.
 * @param sigma_par the scale parameter, a real-valued input.
 *
 * @return a matrix of pseudo-random draws from the Log-Normal distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rlnorm<arma::mat>(5,4,1.0,2.0);
 * \endcode
 *
 * @note This function requires template instantiation, and accepts Armadillo, Blaze, and Eigen dense matrices as output types.
 */

#ifdef STATS_ENABLE_MATRIX_FEATURES
template<typename mT, typename T1, typename T2>
statslib_inline
mT
rlnorm(const ullint_t n, const ullint_t k, const T1 mu_par, const T2 sigma_par)
{
    GEN_MAT_RAND_FN(rlnorm_vec,mu_par,sigma_par);
}
#endif