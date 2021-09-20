#include <gtest/gtest.h>
#include "f3c/qgates/RotationXZ.hpp"

template <typename T>
void test_f3c_qgates_RotationXZ() {

  using R = qclab::real_t< T > ;
  const R pi = 4 * std::atan(1) ;
  const R eps = std::numeric_limits< R >::epsilon() ;

  {
    f3c::qgates::RotationXZ< T >  Rxz ;

    EXPECT_EQ( Rxz.nbQubits() , 2 ) ;   // nbQubits
    EXPECT_FALSE( Rxz.fixed() ) ;       // fixed
    EXPECT_FALSE( Rxz.controlled() ) ;  // controlled

    // matrix
    auto eye = qclab::dense::eye< T >( 4 ) ;
    EXPECT_TRUE( Rxz.matrix() == eye ) ;

    // qubits
    EXPECT_EQ( Rxz.qubits().size() , 2 ) ;
    EXPECT_EQ( Rxz.qubits()[0] , 0 ) ;
    EXPECT_EQ( Rxz.qubits()[1] , 1 ) ;
    int qnew[2] = { 3 , 5 } ;
    Rxz.setQubits( &qnew[0] ) ;
    EXPECT_EQ( Rxz.qubits().size() , 2 ) ;
    EXPECT_EQ( Rxz.qubits()[0] , 3 ) ;
    EXPECT_EQ( Rxz.qubits()[1] , 5 ) ;

    // rotations and thetas
    auto [ rot0 , rot1 ] = Rxz.rotations() ;
    EXPECT_EQ( rot0.theta() , 0 ) ;
    EXPECT_EQ( rot1.theta() , 0 ) ;
    auto [ theta0 , theta1 ] = Rxz.thetas() ;
    EXPECT_EQ( theta0 , 0 ) ;
    EXPECT_EQ( theta1 , 0 ) ;

    // update(rotation0,rotation1)
    qclab::QRotation< R >  new_rot0( 0.5 ) ;
    qclab::QRotation< R >  new_rot1( 0.3 ) ;
    Rxz.update( new_rot0 , new_rot1 ) ;
    {
      auto [ r0 , r1 ] = Rxz.rotations() ;
      EXPECT_TRUE( r0 == new_rot0 ) ;
      EXPECT_TRUE( r1 == new_rot1 ) ;
      auto [ theta0 , theta1 ] = Rxz.thetas() ;
      EXPECT_NEAR( theta0 , 0.5 , eps ) ;
      EXPECT_NEAR( theta1 , 0.3 , eps ) ;
    }

    // update(theta0,theta1)
    theta0 = pi/2 ;
    theta1 = pi/3 ;
    Rxz.update( theta0 , theta1 ) ;
    {
      auto [ theta0 , theta1 ] = Rxz.thetas() ;
      EXPECT_NEAR( theta0 , theta0 , eps ) ;
      EXPECT_NEAR( theta1 , theta1 , eps ) ;
      auto [ r0 , r1 ] = Rxz.rotations() ;
      EXPECT_NEAR( r0.theta() , theta0 , eps ) ;
      EXPECT_NEAR( r0.cos() , std::cos( theta0/2 ) , eps ) ;
      EXPECT_NEAR( r0.sin() , std::sin( theta0/2 ) , eps ) ;
      EXPECT_NEAR( r1.theta() , theta1 , eps ) ;
      EXPECT_NEAR( r1.cos() , std::cos( theta1/2 ) , eps ) ;
      EXPECT_NEAR( r1.sin() , std::sin( theta1/2 ) , eps ) ;
    }

    // matrix
    const T a = T(  std::cos( theta0/2 ) * std::cos( theta1/2 ) ,
                   -std::cos( theta0/2 ) * std::sin( theta1/2 ) ) ;
    const T b = T(  std::cos( theta0/2 ) * std::cos( theta1/2 ) ,
                    std::cos( theta0/2 ) * std::sin( theta1/2 ) ) ;
    const T c = T(  std::sin( theta0/2 ) * std::sin( theta1/2 ) ,
                   -std::sin( theta0/2 ) * std::cos( theta1/2 ) ) ;
    const T d = T( -std::sin( theta0/2 ) * std::sin( theta1/2 ) ,
                   -std::sin( theta0/2 ) * std::cos( theta1/2 ) ) ;

    EXPECT_NEAR( std::real( Rxz.matrix()(0,0) ) , std::real( a ) , eps ) ;
    EXPECT_NEAR( std::real( Rxz.matrix()(1,1) ) , std::real( b ) , eps ) ;
    EXPECT_NEAR( std::real( Rxz.matrix()(2,2) ) , std::real( b ) , eps ) ;
    EXPECT_NEAR( std::real( Rxz.matrix()(3,3) ) , std::real( a ) , eps ) ;
    EXPECT_NEAR( std::imag( Rxz.matrix()(0,0) ) , std::imag( a ) , eps ) ;
    EXPECT_NEAR( std::imag( Rxz.matrix()(1,1) ) , std::imag( b ) , eps ) ;
    EXPECT_NEAR( std::imag( Rxz.matrix()(2,2) ) , std::imag( b ) , eps ) ;
    EXPECT_NEAR( std::imag( Rxz.matrix()(3,3) ) , std::imag( a ) , eps ) ;

    EXPECT_NEAR( std::real( Rxz.matrix()(3,0) ) , std::real( d ) , eps ) ;
    EXPECT_NEAR( std::real( Rxz.matrix()(2,1) ) , std::real( c ) , eps ) ;
    EXPECT_NEAR( std::real( Rxz.matrix()(1,2) ) , std::real( c ) , eps ) ;
    EXPECT_NEAR( std::real( Rxz.matrix()(0,3) ) , std::real( d ) , eps ) ;
    EXPECT_NEAR( std::imag( Rxz.matrix()(3,0) ) , std::imag( d ) , eps ) ;
    EXPECT_NEAR( std::imag( Rxz.matrix()(2,1) ) , std::imag( c ) , eps ) ;
    EXPECT_NEAR( std::imag( Rxz.matrix()(1,2) ) , std::imag( c ) , eps ) ;
    EXPECT_NEAR( std::imag( Rxz.matrix()(0,3) ) , std::imag( d ) , eps ) ;

    EXPECT_EQ( Rxz.matrix()(1,0) , T(0) ) ;
    EXPECT_EQ( Rxz.matrix()(2,0) , T(0) ) ;
    EXPECT_EQ( Rxz.matrix()(0,1) , T(0) ) ;
    EXPECT_EQ( Rxz.matrix()(3,1) , T(0) ) ;
    EXPECT_EQ( Rxz.matrix()(0,2) , T(0) ) ;
    EXPECT_EQ( Rxz.matrix()(3,2) , T(0) ) ;
    EXPECT_EQ( Rxz.matrix()(1,3) , T(0) ) ;
    EXPECT_EQ( Rxz.matrix()(2,3) , T(0) ) ;

    // print
    Rxz.print() ;

    // toQASM
    {
      std::stringstream qasm ;
      EXPECT_EQ( Rxz.toQASM( qasm ) , 0 ) ;
      auto [ theta0 , theta1 ] = Rxz.thetas() ;
      auto str_theta0 = qclab::qasm( theta0 ) ;
      auto str_theta1 = qclab::qasm( theta1 ) ;
      std::string qasm_check =
        std::string( "cx q[3], q[5];\n" ) +
        "rx(" + str_theta0 + ") q[3];\n" + "rz(" + str_theta1 + ") q[5];\n" +
        "cx q[3], q[5];\n" ;
      EXPECT_EQ( qasm.str() , qasm_check ) ;
      std::cout << qasm.str() ;
    }

    // operators == and !=
    {
      qclab::QRotation< R >  new_rot0( std::cos( pi/4 ) , std::sin( pi/4 ) ) ;
      qclab::QRotation< R >  new_rot1( std::cos( pi/6 ) , std::sin( pi/6 ) ) ;
      f3c::qgates::RotationXZ< T >  Rxz2( new_rot0 , new_rot1 ) ;
      EXPECT_TRUE( Rxz == Rxz2 ) ;
      EXPECT_FALSE( Rxz != Rxz2 ) ;
      Rxz2.update( 1 , 2 ) ;
      EXPECT_TRUE( Rxz != Rxz2 ) ;
      EXPECT_FALSE( Rxz == Rxz2 ) ;
    }
  }


  //
  // constructors without qubits
  //
  {
    qclab::QRotation< R >         rot0( pi/4 ) ;
    qclab::QRotation< R >         rot1( pi/3 ) ;
    f3c::qgates::RotationXZ< T >  Rxz( rot0 , rot1 ) ;

    EXPECT_EQ( Rxz.nbQubits() , 2 ) ;          // nbQubits
    EXPECT_FALSE( Rxz.fixed() ) ;              // fixed
    EXPECT_FALSE( Rxz.controlled() ) ;         // controlled

    auto qubits = Rxz.qubits() ;
    EXPECT_EQ( qubits[0] , 0 ) ;               // qubit0
    EXPECT_EQ( qubits[1] , 1 ) ;               // qubit1

    auto [ r0 , r1 ] = Rxz.rotations() ;
    EXPECT_TRUE( r0 == rot0 ) ;                // rot0
    EXPECT_TRUE( r1 == rot1 ) ;                // rot1

    auto [ theta0 , theta1 ] = Rxz.thetas() ;
    EXPECT_NEAR( theta0 , pi/4 , eps ) ;       // theta0
    EXPECT_NEAR( theta1 , pi/3 , eps ) ;       // theta1
  }

  {
    const R theta0( pi/4 ) ;
    const R theta1( pi/3 ) ;
    f3c::qgates::RotationXZ< T >  Rxz( theta0 , theta1 ) ;

    EXPECT_EQ( Rxz.nbQubits() , 2 ) ;           // nbQubits
    EXPECT_FALSE( Rxz.fixed() ) ;               // fixed
    EXPECT_FALSE( Rxz.controlled() ) ;          // controlled

    auto qubits = Rxz.qubits() ;
    EXPECT_EQ( qubits[0] , 0 ) ;                // qubit0
    EXPECT_EQ( qubits[1] , 1 ) ;                // qubit1

    auto [ r0 , r1 ] = Rxz.rotations() ;
    EXPECT_NEAR( r0.theta() , theta0 , eps ) ;  // rot0
    EXPECT_NEAR( r1.theta() , theta1 , eps ) ;  // rot1

    auto [ th0 , th1 ] = Rxz.thetas() ;
    EXPECT_NEAR( th0 , theta0 , eps ) ;         // theta0
    EXPECT_NEAR( th1 , theta1 , eps ) ;         // theta1
  }


  //
  // constructors with qubit0 and qubit1
  //
  {
    int qubit0 = 3 ;
    int qubit1 = 5 ;
    qclab::QRotation< R >         rot0( pi/4 ) ;
    qclab::QRotation< R >         rot1( pi/3 ) ;
    f3c::qgates::RotationXZ< T >  Rxz( qubit0 , qubit1 , rot0 , rot1 ) ;

    EXPECT_EQ( Rxz.nbQubits() , 2 ) ;          // nbQubits
    EXPECT_FALSE( Rxz.fixed() ) ;              // fixed
    EXPECT_FALSE( Rxz.controlled() ) ;         // controlled

    auto qubits = Rxz.qubits() ;
    EXPECT_EQ( qubits[0] , qubit0 ) ;          // qubit0
    EXPECT_EQ( qubits[1] , qubit1 ) ;          // qubit1

    auto [ r0 , r1 ] = Rxz.rotations() ;
    EXPECT_TRUE( r0 == rot0 ) ;                // rot0
    EXPECT_TRUE( r1 == rot1 ) ;                // rot1

    auto [ theta0 , theta1 ] = Rxz.thetas() ;
    EXPECT_NEAR( theta0 , pi/4 , eps ) ;       // theta0
    EXPECT_NEAR( theta1 , pi/3 , eps ) ;       // theta1
  }

  {
    int qubit0 = 3 ;
    int qubit1 = 5 ;
    const R theta0( pi/4 ) ;
    const R theta1( pi/3 ) ;
    f3c::qgates::RotationXZ< T >  Rxz( qubit0 , qubit1 , theta0 , theta1 ) ;

    EXPECT_EQ( Rxz.nbQubits() , 2 ) ;           // nbQubits
    EXPECT_FALSE( Rxz.fixed() ) ;               // fixed
    EXPECT_FALSE( Rxz.controlled() ) ;          // controlled

    auto qubits = Rxz.qubits() ;
    EXPECT_EQ( qubits[0] , qubit0 ) ;           // qubit0
    EXPECT_EQ( qubits[1] , qubit1 ) ;           // qubit1

    auto [ r0 , r1 ] = Rxz.rotations() ;
    EXPECT_NEAR( r0.theta() , theta0 , eps ) ;  // rot0
    EXPECT_NEAR( r1.theta() , theta1 , eps ) ;  // rot1

    auto [ th0 , th1 ] = Rxz.thetas() ;
    EXPECT_NEAR( th0 , theta0 , eps ) ;         // theta0
    EXPECT_NEAR( th1 , theta1 , eps ) ;         // theta1
  }


  //
  // operators
  //
  {
    const R thetaA0 = pi/2 ;
    const R thetaA1 = pi/3 ;
    f3c::qgates::RotationXZ< T >  RxzA( thetaA0 , thetaA1 ) ;

    const R thetaB0 = pi/4 ;
    const R thetaB1 = pi/5 ;
    f3c::qgates::RotationXZ< T >  RxzB( thetaB0 , thetaB1 ) ;

    // operator *=
    RxzA *= RxzB ;
    const R theta0 = thetaA0 + thetaB0 ;
    const R theta1 = thetaA1 + thetaB1 ;
    auto [ th0 , th1 ] = RxzA.thetas() ;
    EXPECT_NEAR( th0 , theta0 , 10*eps ) ;    // thetaA0 = theta0
    EXPECT_NEAR( th1 , theta1 , 10*eps ) ;    // thetaA1 = theta1
    auto [ thB0 , thB1 ] = RxzB.thetas() ;
    EXPECT_NEAR( thB0 , thetaB0 , 10*eps ) ;  // thetaB0
    EXPECT_NEAR( thB1 , thetaB1 , 10*eps ) ;  // thetaB1
  }

  {
    const R thetaA0 = pi/2 ;
    const R thetaA1 = pi/3 ;
    f3c::qgates::RotationXZ< T >  RxzA( thetaA0 , thetaA1 ) ;

    const R thetaB0 = pi/4 ;
    const R thetaB1 = pi/5 ;
    f3c::qgates::RotationXZ< T >  RxzB( thetaB0 , thetaB1 ) ;

    // operator /=
    RxzA /= RxzB ;
    const R theta0 = thetaA0 - thetaB0 ;
    const R theta1 = thetaA1 - thetaB1 ;
    auto [ th0 , th1 ] = RxzA.thetas() ;
    EXPECT_NEAR( th0 , theta0 , 10*eps ) ;    // thetaA0 = theta0
    EXPECT_NEAR( th1 , theta1 , 10*eps ) ;    // thetaA1 = theta1
    auto [ thB0 , thB1 ] = RxzB.thetas() ;
    EXPECT_NEAR( thB0 , thetaB0 , 10*eps ) ;  // thetaB0
    EXPECT_NEAR( thB1 , thetaB1 , 10*eps ) ;  // thetaB1
  }

  {
    const R thetaA0 = pi/2 ;
    const R thetaA1 = pi/3 ;
    f3c::qgates::RotationXZ< T >  RxzA( thetaA0 , thetaA1 ) ;

    const R thetaB0 = pi/4 ;
    const R thetaB1 = pi/5 ;
    f3c::qgates::RotationXZ< T >  RxzB( thetaB0 , thetaB1 ) ;

    // operator *
    f3c::qgates::RotationXZ< T > RxzC = RxzA * RxzB ;
    const R thetaC0 = thetaA0 + thetaB0 ;
    const R thetaC1 = thetaA1 + thetaB1 ;
    auto [ thA0 , thA1 ] = RxzA.thetas() ;
    EXPECT_NEAR( thA0 , thetaA0 , 10*eps ) ;  // thetaA0
    EXPECT_NEAR( thA1 , thetaA1 , 10*eps ) ;  // thetaA1
    auto [ thB0 , thB1 ] = RxzB.thetas() ;
    EXPECT_NEAR( thB0 , thetaB0 , 10*eps ) ;  // thetaB0
    EXPECT_NEAR( thB1 , thetaB1 , 10*eps ) ;  // thetaB1
    auto [ thC0 , thC1 ] = RxzC.thetas() ;
    EXPECT_NEAR( thC0 , thetaC0 , 10*eps ) ;  // thetaC0
    EXPECT_NEAR( thC1 , thetaC1 , 10*eps ) ;  // thetaC1
  }

  {
    const R thetaA0 = pi/2 ;
    const R thetaA1 = pi/3 ;
    f3c::qgates::RotationXZ< T >  RxzA( thetaA0 , thetaA1 ) ;

    const R thetaB0 = pi/4 ;
    const R thetaB1 = pi/5 ;
    f3c::qgates::RotationXZ< T >  RxzB( thetaB0 , thetaB1 ) ;

    // operator /
    f3c::qgates::RotationXZ< T > RxzC = RxzA / RxzB ;
    const R thetaC0 = thetaA0 - thetaB0 ;
    const R thetaC1 = thetaA1 - thetaB1 ;
    auto [ thA0 , thA1 ] = RxzA.thetas() ;
    EXPECT_NEAR( thA0 , thetaA0 , 10*eps ) ;  // thetaA0
    EXPECT_NEAR( thA1 , thetaA1 , 10*eps ) ;  // thetaA1
    auto [ thB0 , thB1 ] = RxzB.thetas() ;
    EXPECT_NEAR( thB0 , thetaB0 , 10*eps ) ;  // thetaB0
    EXPECT_NEAR( thB1 , thetaB1 , 10*eps ) ;  // thetaB1
    auto [ thC0 , thC1 ] = RxzC.thetas() ;
    EXPECT_NEAR( thC0 , thetaC0 , 10*eps ) ;  // thetaC0
    EXPECT_NEAR( thC1 , thetaC1 , 10*eps ) ;  // thetaC1
  }

  {
    const R thetaA0 = pi/2 ;
    const R thetaA1 = pi/3 ;
    f3c::qgates::RotationXZ< T >  RxzA( thetaA0 , thetaA1 ) ;

    // inv
    f3c::qgates::RotationXZ< T >  RxzB = RxzA.inv() ;
    auto [ thA0 , thA1 ] = RxzA.thetas() ;
    EXPECT_NEAR( thA0 , thetaA0 , 10*eps ) ;  // thetaA0
    EXPECT_NEAR( thA1 , thetaA1 , 10*eps ) ;  // thetaA1
    auto [ thB0 , thB1 ] = RxzB.thetas() ;
    EXPECT_NEAR( thB0 , -thetaA0 , 10*eps ) ;  // thetaB0
    EXPECT_NEAR( thB1 , -thetaA1 , 10*eps ) ;  // thetaB1
  }

}


/*
 * complex float
 */
TEST( f3c_qgates_RotationXZ , complex_float ) {
  test_f3c_qgates_RotationXZ< std::complex< float > >() ;
}

/*
 * complex double
 */
TEST( f3c_qgates_RotationXZ , complex_double ) {
  test_f3c_qgates_RotationXZ< std::complex< double > >() ;
}

