#include <gtest/gtest.h>
#include "f3c/qgates/RotationTFXY.hpp"
#include "f3c/qgates/RotationTFXYMatrix.hpp"

template <typename T>
void test_f3c_qgates_RotationTFXY() {

  using R = qclab::real_t< T > ;
  const R pi = 4 * std::atan(1) ;
  const R eps = std::numeric_limits< R >::epsilon() ;

  {
    f3c::qgates::RotationTFXY< T >  TFRxy ;

    EXPECT_EQ( TFRxy.nbQubits() , 2 ) ;   // nbQubits
    EXPECT_FALSE( TFRxy.fixed() ) ;       // fixed
    EXPECT_FALSE( TFRxy.controlled() ) ;  // controlled

    // matrix
    auto eye = qclab::dense::eye< T >( 4 ) ;
    EXPECT_TRUE( TFRxy.matrix() == eye ) ;

    // qubits
    EXPECT_EQ( TFRxy.qubits().size() , 2 ) ;
    EXPECT_EQ( TFRxy.qubits()[0] , 0 ) ;
    EXPECT_EQ( TFRxy.qubits()[1] , 1 ) ;
    int qnew[2] = { 3 , 5 } ;
    TFRxy.setQubits( &qnew[0] ) ;
    EXPECT_EQ( TFRxy.qubits().size() , 2 ) ;
    EXPECT_EQ( TFRxy.qubits()[0] , 3 ) ;
    EXPECT_EQ( TFRxy.qubits()[1] , 5 ) ;

    // rotations and thetas
    auto [ rot0 , rot1 , rot2 , rot3 , rot4 , rot5 ] = TFRxy.rotations() ;
    EXPECT_EQ( rot0.theta() , 0 ) ;
    EXPECT_EQ( rot1.theta() , 0 ) ;
    EXPECT_EQ( rot2.theta() , 0 ) ;
    EXPECT_EQ( rot3.theta() , 0 ) ;
    EXPECT_EQ( rot4.theta() , 0 ) ;
    EXPECT_EQ( rot5.theta() , 0 ) ;
    auto [ th0 , th1 , th2 , th3 , th4 , th5 ] = TFRxy.thetas() ;
    EXPECT_EQ( th0 , 0 ) ;
    EXPECT_EQ( th1 , 0 ) ;
    EXPECT_EQ( th2 , 0 ) ;
    EXPECT_EQ( th3 , 0 ) ;
    EXPECT_EQ( th4 , 0 ) ;
    EXPECT_EQ( th5 , 0 ) ;

    // update(rotation0,rotation1,rotation2,rotation3,rotation4,rotation5)
    const R theta0(  pi/4 ) ;
    const R theta1(  pi/3 ) ;
    const R theta2(  pi/2 ) ;
    const R theta3( -pi/7 ) ;
    const R theta4( -pi/5 ) ;
    const R theta5(  pi/9 ) ;
    qclab::QRotation< R >  rot0n( theta0 ) ;
    qclab::QRotation< R >  rot1n( theta1 ) ;
    qclab::QRotation< R >  rot2n( theta2 ) ;
    qclab::QRotation< R >  rot3n( theta3 ) ;
    qclab::QRotation< R >  rot4n( theta4 ) ;
    qclab::QRotation< R >  rot5n( theta5 ) ;
    TFRxy.update( rot0n , rot1n , rot2n , rot3n , rot4n , rot5n  ) ;
    {
      EXPECT_TRUE( TFRxy.rotation0() == rot0n ) ;
      EXPECT_TRUE( TFRxy.rotation1() == rot1n ) ;
      EXPECT_TRUE( TFRxy.rotation2() == rot2n ) ;
      EXPECT_TRUE( TFRxy.rotation3() == rot3n ) ;
      EXPECT_TRUE( TFRxy.rotation4() == rot4n ) ;
      EXPECT_TRUE( TFRxy.rotation5() == rot5n ) ;
      EXPECT_NEAR( TFRxy.theta0() , theta0 , eps ) ;
      EXPECT_NEAR( TFRxy.theta1() , theta1 , eps ) ;
      EXPECT_NEAR( TFRxy.theta2() , theta2 , eps ) ;
      EXPECT_NEAR( TFRxy.theta3() , theta3 , eps ) ;
      EXPECT_NEAR( TFRxy.theta4() , theta4 , eps ) ;
      EXPECT_NEAR( TFRxy.theta5() , theta5 , eps ) ;
    }
    TFRxy.update( 0 , 0 , 0 , 0 , 0 , 0 ) ;
    EXPECT_EQ( TFRxy.rotation0().theta() , 0 ) ;
    EXPECT_EQ( TFRxy.rotation1().theta() , 0 ) ;
    EXPECT_EQ( TFRxy.rotation2().theta() , 0 ) ;
    EXPECT_EQ( TFRxy.rotation3().theta() , 0 ) ;
    EXPECT_EQ( TFRxy.rotation4().theta() , 0 ) ;
    EXPECT_EQ( TFRxy.rotation5().theta() , 0 ) ;

    // update(theta0,theta1,theta2,theta3,theta4,theta5)
    TFRxy.update( theta0 , theta1 , theta2 , theta3 , theta4 , theta5 ) ;
    EXPECT_NEAR( TFRxy.theta0() , theta0 , eps ) ;
    EXPECT_NEAR( TFRxy.theta1() , theta1 , eps ) ;
    EXPECT_NEAR( TFRxy.theta2() , theta2 , eps ) ;
    EXPECT_NEAR( TFRxy.theta3() , theta3 , eps ) ;
    EXPECT_NEAR( TFRxy.theta4() , theta4 , eps ) ;
    EXPECT_NEAR( TFRxy.theta5() , theta5 , eps ) ;

    // matrix
    const auto mat = TFRxy.matrix() ;
    EXPECT_NEAR( std::real( mat(0,0) ) ,  std::real( TFRxy.a() ) , eps ) ;
    EXPECT_NEAR( std::imag( mat(0,0) ) ,  std::imag( TFRxy.a() ) , eps ) ;
    EXPECT_NEAR( std::real( mat(1,1) ) ,  std::real( TFRxy.b() ) , eps ) ;
    EXPECT_NEAR( std::imag( mat(1,1) ) ,  std::imag( TFRxy.b() ) , eps ) ;
    EXPECT_NEAR( std::real( mat(2,1) ) ,  std::real( TFRxy.c() ) , eps ) ;
    EXPECT_NEAR( std::imag( mat(2,1) ) ,  std::imag( TFRxy.c() ) , eps ) ;
    EXPECT_NEAR( std::real( mat(3,0) ) ,  std::real( TFRxy.d() ) , eps ) ;
    EXPECT_NEAR( std::imag( mat(3,0) ) ,  std::imag( TFRxy.d() ) , eps ) ;

    EXPECT_NEAR( std::real( mat(3,3) ) ,  std::real( TFRxy.a() ) , eps ) ;
    EXPECT_NEAR( std::imag( mat(3,3) ) , -std::imag( TFRxy.a() ) , eps ) ;
    EXPECT_NEAR( std::real( mat(2,2) ) ,  std::real( TFRxy.b() ) , eps ) ;
    EXPECT_NEAR( std::imag( mat(2,2) ) , -std::imag( TFRxy.b() ) , eps ) ;
    EXPECT_NEAR( std::real( mat(1,2) ) , -std::real( TFRxy.c() ) , eps ) ;
    EXPECT_NEAR( std::imag( mat(1,2) ) ,  std::imag( TFRxy.c() ) , eps ) ;
    EXPECT_NEAR( std::real( mat(0,3) ) , -std::real( TFRxy.d() ) , eps ) ;
    EXPECT_NEAR( std::imag( mat(0,3) ) ,  std::imag( TFRxy.d() ) , eps ) ;

    EXPECT_EQ( TFRxy.matrix()(1,0) , T(0) ) ;
    EXPECT_EQ( TFRxy.matrix()(2,0) , T(0) ) ;
    EXPECT_EQ( TFRxy.matrix()(0,1) , T(0) ) ;
    EXPECT_EQ( TFRxy.matrix()(3,1) , T(0) ) ;
    EXPECT_EQ( TFRxy.matrix()(0,2) , T(0) ) ;
    EXPECT_EQ( TFRxy.matrix()(3,2) , T(0) ) ;
    EXPECT_EQ( TFRxy.matrix()(1,3) , T(0) ) ;
    EXPECT_EQ( TFRxy.matrix()(2,3) , T(0) ) ;

    // print
    TFRxy.print() ;

    // toQASM
    {
      std::stringstream qasm ;
      EXPECT_EQ( TFRxy.toQASM( qasm ) , 0 ) ;
      auto str_pi = qclab::qasm( pi/2 ) ;
      auto str_theta0 = qclab::qasm( TFRxy.theta0() ) ;
      auto str_theta1 = qclab::qasm( TFRxy.theta1() ) ;
      auto str_theta2 = qclab::qasm( TFRxy.theta2() ) ;
      auto str_theta3 = qclab::qasm( TFRxy.theta3() ) ;
      auto str_theta4 = qclab::qasm( TFRxy.theta4() ) ;
      auto str_theta5 = qclab::qasm( TFRxy.theta5() ) ;
      std::string qasm_check =
        "rz(" + str_theta0 + ") q[3];\n" + "rz(" + str_theta1 + ") q[5];\n" +
        "rx(" + str_pi + ") q[3];\n"     + "rx(" + str_pi + ") q[5];\n" +
        "cx q[3], q[5];\n" +
        "rx(" + str_theta2 + ") q[3];\n" + "rz(" + str_theta3 + ") q[5];\n" +
        "cx q[3], q[5];\n" +
        "rx(-" + str_pi + ") q[3];\n"    + "rx(-" + str_pi + ") q[5];\n" +
        "rz(" + str_theta4 + ") q[3];\n" + "rz(" + str_theta5 + ") q[5];\n" ;
      EXPECT_EQ( qasm.str() , qasm_check ) ;
      std::cout << qasm.str() ;
    }

    // operators == and !=
    {
      f3c::qgates::RotationTFXY< T >  TFRxy2( theta0 , theta1 , theta2 ,
                                              theta3 , theta4 , theta5 ) ;
      EXPECT_TRUE( TFRxy == TFRxy2 ) ;
      EXPECT_FALSE( TFRxy != TFRxy2 ) ;
      TFRxy2.update( 1 , 2 , 3 , 4 , 5 , 6 ) ;
      EXPECT_TRUE( TFRxy != TFRxy2 ) ;
      EXPECT_FALSE( TFRxy == TFRxy2 ) ;
    }
  }


  //
  // constructors without qubits
  //
  {
    const R theta0(  pi/4 ) ;
    const R theta1(  pi/3 ) ;
    qclab::QRotation< R >  rot0( theta0 ) ;
    qclab::QRotation< R >  rot1( theta1 ) ;

    const R theta2(  pi/2 ) ;
    const R theta3( -pi/7 ) ;
    qclab::QRotation< R >  rot2( theta2 ) ;
    qclab::QRotation< R >  rot3( theta3 ) ;

    const R theta4( -pi/5 ) ;
    const R theta5(  pi/9 ) ;
    qclab::QRotation< R >  rot4( theta4 ) ;
    qclab::QRotation< R >  rot5( theta5 ) ;

    f3c::qgates::RotationTFXY< T >  TFRxy( rot0 , rot1 , rot2 ,
                                           rot3 , rot4 , rot5 ) ;

    EXPECT_EQ( TFRxy.nbQubits() , 2 ) ;   // nbQubits
    EXPECT_FALSE( TFRxy.fixed() ) ;       // fixed
    EXPECT_FALSE( TFRxy.controlled() ) ;  // controlled

    auto qubits = TFRxy.qubits() ;
    EXPECT_EQ( qubits[0] , 0 ) ;          // qubit0
    EXPECT_EQ( qubits[1] , 1 ) ;          // qubit1

    auto [ r0 , r1 , r2 , r3 , r4 , r5 ] = TFRxy.rotations() ;
    EXPECT_TRUE( r0 == rot0 ) ;           // rot0
    EXPECT_TRUE( r1 == rot1 ) ;           // rot1
    EXPECT_TRUE( r2 == rot2 ) ;           // rot2
    EXPECT_TRUE( r3 == rot3 ) ;           // rot3
    EXPECT_TRUE( r4 == rot4 ) ;           // rot4
    EXPECT_TRUE( r5 == rot5 ) ;           // rot5

    auto [ th0 , th1 , th2 , th3 , th4 , th5 ] = TFRxy.thetas() ;
    EXPECT_NEAR( th0 , theta0 , eps ) ;   // theta0
    EXPECT_NEAR( th1 , theta1 , eps ) ;   // theta1
    EXPECT_NEAR( th2 , theta2 , eps ) ;   // theta2
    EXPECT_NEAR( th3 , theta3 , eps ) ;   // theta3
    EXPECT_NEAR( th4 , theta4 , eps ) ;   // theta4
    EXPECT_NEAR( th5 , theta5 , eps ) ;   // theta5

    const T a(  3.794721175389957e-01 , -3.729062113342866e-01 ) ;
    const T b(  6.893313103595740e-01 ,  4.916952451638431e-01 ) ;
    const T c( -1.863215602624727e-01 , -4.983396498599911e-01 ) ;
    const T d( -7.369512296884874e-01 , -4.169469446097490e-01 ) ;

    EXPECT_NEAR( std::real( TFRxy.a() ) , std::real( a ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.a() ) , std::imag( a ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.b() ) , std::real( b ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.b() ) , std::imag( b ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.c() ) , std::real( c ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.c() ) , std::imag( c ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.d() ) , std::real( d ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.d() ) , std::imag( d ) , eps ) ;
  }

  {
    const R theta0(  pi/4 ) ;
    const R theta1(  pi/3 ) ;
    const R theta2(  pi/2 ) ;
    const R theta3( -pi/7 ) ;
    const R theta4( -pi/5 ) ;
    const R theta5(  pi/9 ) ;
    f3c::qgates::RotationTFXY< T >  TFRxy( theta0 , theta1 , theta2 ,
                                           theta3 , theta4 , theta5 ) ;

    EXPECT_EQ( TFRxy.nbQubits() , 2 ) ;         // nbQubits
    EXPECT_FALSE( TFRxy.fixed() ) ;             // fixed
    EXPECT_FALSE( TFRxy.controlled() ) ;        // controlled

    auto qubits = TFRxy.qubits() ;
    EXPECT_EQ( qubits[0] , 0 ) ;                // qubit0
    EXPECT_EQ( qubits[1] , 1 ) ;                // qubit1

    auto [ th0 , th1 , th2 , th3 , th4 , th5 ] = TFRxy.thetas() ;
    EXPECT_NEAR( th0 , theta0 , eps ) ;         // theta0
    EXPECT_NEAR( th1 , theta1 , eps ) ;         // theta1
    EXPECT_NEAR( th2 , theta2 , eps ) ;         // theta2
    EXPECT_NEAR( th3 , theta3 , eps ) ;         // theta3
    EXPECT_NEAR( th4 , theta4 , eps ) ;         // theta4
    EXPECT_NEAR( th5 , theta5 , eps ) ;         // theta5

    auto [ r0 , r1 , r2 , r3 , r4 , r5 ] = TFRxy.rotations() ;
    EXPECT_NEAR( r0.theta() , theta0 , eps ) ;  // rot0
    EXPECT_NEAR( r1.theta() , theta1 , eps ) ;  // rot1
    EXPECT_NEAR( r2.theta() , theta2 , eps ) ;  // rot2
    EXPECT_NEAR( r3.theta() , theta3 , eps ) ;  // rot3
    EXPECT_NEAR( r4.theta() , theta4 , eps ) ;  // rot4
    EXPECT_NEAR( r5.theta() , theta5 , eps ) ;  // rot5

    const T a(  3.794721175389957e-01 , -3.729062113342866e-01 ) ;
    const T b(  6.893313103595740e-01 ,  4.916952451638431e-01 ) ;
    const T c( -1.863215602624727e-01 , -4.983396498599911e-01 ) ;
    const T d( -7.369512296884874e-01 , -4.169469446097490e-01 ) ;

    EXPECT_NEAR( std::real( TFRxy.a() ) , std::real( a ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.a() ) , std::imag( a ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.b() ) , std::real( b ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.b() ) , std::imag( b ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.c() ) , std::real( c ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.c() ) , std::imag( c ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.d() ) , std::real( d ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.d() ) , std::imag( d ) , eps ) ;
  }


  //
  // constructors with qubit0 and qubit1
  //
  {
    int qubit0 = 3 ;
    int qubit1 = 5 ;

    const R theta0(  pi/4 ) ;
    const R theta1(  pi/3 ) ;
    qclab::QRotation< R >  rot0( theta0 ) ;
    qclab::QRotation< R >  rot1( theta1 ) ;

    const R theta2(  pi/2 ) ;
    const R theta3( -pi/7 ) ;
    qclab::QRotation< R >  rot2( theta2 ) ;
    qclab::QRotation< R >  rot3( theta3 ) ;

    const R theta4( -pi/5 ) ;
    const R theta5(  pi/9 ) ;
    qclab::QRotation< R >  rot4( theta4 ) ;
    qclab::QRotation< R >  rot5( theta5 ) ;

    f3c::qgates::RotationTFXY< T >  TFRxy( qubit0 , qubit1 ,
                                           rot0 , rot1 , rot2 ,
                                           rot3 , rot4 , rot5 ) ;

    EXPECT_EQ( TFRxy.nbQubits() , 2 ) ;   // nbQubits
    EXPECT_FALSE( TFRxy.fixed() ) ;       // fixed
    EXPECT_FALSE( TFRxy.controlled() ) ;  // controlled

    auto qubits = TFRxy.qubits() ;
    EXPECT_EQ( qubits[0] , qubit0 ) ;     // qubit0
    EXPECT_EQ( qubits[1] , qubit1 ) ;     // qubit1

    auto [ r0 , r1 , r2 , r3 , r4 , r5 ] = TFRxy.rotations() ;
    EXPECT_TRUE( r0 == rot0 ) ;           // rot0
    EXPECT_TRUE( r1 == rot1 ) ;           // rot1
    EXPECT_TRUE( r2 == rot2 ) ;           // rot2
    EXPECT_TRUE( r3 == rot3 ) ;           // rot3
    EXPECT_TRUE( r4 == rot4 ) ;           // rot4
    EXPECT_TRUE( r5 == rot5 ) ;           // rot5

    auto [ th0 , th1 , th2 , th3 , th4 , th5 ] = TFRxy.thetas() ;
    EXPECT_NEAR( th0 , theta0 , eps ) ;   // theta0
    EXPECT_NEAR( th1 , theta1 , eps ) ;   // theta1
    EXPECT_NEAR( th2 , theta2 , eps ) ;   // theta2
    EXPECT_NEAR( th3 , theta3 , eps ) ;   // theta3
    EXPECT_NEAR( th4 , theta4 , eps ) ;   // theta4
    EXPECT_NEAR( th5 , theta5 , eps ) ;   // theta5

    const T a(  3.794721175389957e-01 , -3.729062113342866e-01 ) ;
    const T b(  6.893313103595740e-01 ,  4.916952451638431e-01 ) ;
    const T c( -1.863215602624727e-01 , -4.983396498599911e-01 ) ;
    const T d( -7.369512296884874e-01 , -4.169469446097490e-01 ) ;

    EXPECT_NEAR( std::real( TFRxy.a() ) , std::real( a ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.a() ) , std::imag( a ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.b() ) , std::real( b ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.b() ) , std::imag( b ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.c() ) , std::real( c ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.c() ) , std::imag( c ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.d() ) , std::real( d ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.d() ) , std::imag( d ) , eps ) ;
  }

  {
    int qubit0 = 3 ;
    int qubit1 = 5 ;
    const R theta0(  pi/4 ) ;
    const R theta1(  pi/3 ) ;
    const R theta2(  pi/2 ) ;
    const R theta3( -pi/7 ) ;
    const R theta4( -pi/5 ) ;
    const R theta5(  pi/9 ) ;
    f3c::qgates::RotationTFXY< T >  TFRxy( qubit0 , qubit1 ,
                                           theta0 , theta1 , theta2 ,
                                           theta3 , theta4 , theta5 ) ;

    EXPECT_EQ( TFRxy.nbQubits() , 2 ) ;         // nbQubits
    EXPECT_FALSE( TFRxy.fixed() ) ;             // fixed
    EXPECT_FALSE( TFRxy.controlled() ) ;        // controlled

    auto qubits = TFRxy.qubits() ;
    EXPECT_EQ( qubits[0] , qubit0 ) ;           // qubit0
    EXPECT_EQ( qubits[1] , qubit1 ) ;           // qubit1

    auto [ th0 , th1 , th2 , th3 , th4 , th5 ] = TFRxy.thetas() ;
    EXPECT_NEAR( th0 , theta0 , eps ) ;         // theta0
    EXPECT_NEAR( th1 , theta1 , eps ) ;         // theta1
    EXPECT_NEAR( th2 , theta2 , eps ) ;         // theta2
    EXPECT_NEAR( th3 , theta3 , eps ) ;         // theta3
    EXPECT_NEAR( th4 , theta4 , eps ) ;         // theta4
    EXPECT_NEAR( th5 , theta5 , eps ) ;         // theta5

    auto [ r0 , r1 , r2 , r3 , r4 , r5 ] = TFRxy.rotations() ;
    EXPECT_NEAR( r0.theta() , theta0 , eps ) ;  // rot0
    EXPECT_NEAR( r1.theta() , theta1 , eps ) ;  // rot1
    EXPECT_NEAR( r2.theta() , theta2 , eps ) ;  // rot2
    EXPECT_NEAR( r3.theta() , theta3 , eps ) ;  // rot3
    EXPECT_NEAR( r4.theta() , theta4 , eps ) ;  // rot4
    EXPECT_NEAR( r5.theta() , theta5 , eps ) ;  // rot5

    const T a(  3.794721175389957e-01 , -3.729062113342866e-01 ) ;
    const T b(  6.893313103595740e-01 ,  4.916952451638431e-01 ) ;
    const T c( -1.863215602624727e-01 , -4.983396498599911e-01 ) ;
    const T d( -7.369512296884874e-01 , -4.169469446097490e-01 ) ;

    EXPECT_NEAR( std::real( TFRxy.a() ) , std::real( a ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.a() ) , std::imag( a ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.b() ) , std::real( b ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.b() ) , std::imag( b ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.c() ) , std::real( c ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.c() ) , std::imag( c ) , eps ) ;
    EXPECT_NEAR( std::real( TFRxy.d() ) , std::real( d ) , eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.d() ) , std::imag( d ) , eps ) ;
  }


  //
  // constructor with gate
  //
  {
    int qubit0 = 3 ;
    int qubit1 = 5 ;
    const T a( -5.049262824994509e-01 , -1.183280215457461e-01 ) ;
    const T b( -1.646607339353139e-01 , -8.390082069075593e-01 ) ;
    const T c( -2.653946050859590e-01 ,  4.455533357892336e-01 ) ;
    const T d( -4.895245818757411e-01 , -7.010089958750423e-01 ) ;
    f3c::qgates::RotationTFXYMatrix< T >  TFRxyMat( qubit0 , qubit1 ,
                                                    a , b , c , d ) ;

    f3c::qgates::RotationTFXY< T >  TFRxy( TFRxyMat ) ;

    EXPECT_EQ( TFRxy.nbQubits() , 2 ) ;   // nbQubits
    EXPECT_FALSE( TFRxy.fixed() ) ;       // fixed
    EXPECT_FALSE( TFRxy.controlled() ) ;  // controlled

    auto qubits = TFRxy.qubits() ;
    EXPECT_EQ( qubits[0] , qubit0 ) ;     // qubit0
    EXPECT_EQ( qubits[1] , qubit1 ) ;     // qubit1

    EXPECT_NEAR( std::real( TFRxy.a() ) , std::real( a ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.a() ) , std::imag( a ) , 10*eps ) ;
    EXPECT_NEAR( std::real( TFRxy.b() ) , std::real( b ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.b() ) , std::imag( b ) , 10*eps ) ;
    EXPECT_NEAR( std::real( TFRxy.c() ) , std::real( c ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.c() ) , std::imag( c ) , 10*eps ) ;
    EXPECT_NEAR( std::real( TFRxy.d() ) , std::real( d ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.d() ) , std::imag( d ) , 10*eps ) ;

    EXPECT_EQ( TFRxyMat.a() , a ) ;
    EXPECT_EQ( TFRxyMat.b() , b ) ;
    EXPECT_EQ( TFRxyMat.c() , c ) ;
    EXPECT_EQ( TFRxyMat.d() , d ) ;
  }


  //
  // numerical values a,b,c,d
  //
  {
    const R theta0 = -0.17 ;
    const R theta1 =  1.05 ;
    const R theta2 =  0.77 ;
    const R theta3 =  0.64 ;
    const R theta4 = -1.25 ;
    const R theta5 = -0.89 ;
    f3c::qgates::RotationTFXY< T >  TFRxy( theta0 , theta1 , theta2 ,
                                           theta3 , theta4 , theta5 ) ;

    EXPECT_NEAR( std::real( TFRxy.a() ) ,  8.063211511077109e-01 , 10*eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.a() ) ,  5.879006277711651e-01 , 10*eps ) ;
    EXPECT_NEAR( std::real( TFRxy.b() ) ,  5.360567230543576e-01 , 10*eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.b() ) ,  5.410132581052328e-01 , 10*eps ) ;
    EXPECT_NEAR( std::real( TFRxy.c() ) ,  2.701463825197830e-01 , 10*eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.c() ) , -5.890405556785199e-01 , 10*eps ) ;
    EXPECT_NEAR( std::real( TFRxy.d() ) , -6.483423409213447e-02 , 10*eps ) ;
    EXPECT_NEAR( std::imag( TFRxy.d() ) , -3.946546882058144e-03 , 10*eps ) ;
  }


  //
  // operators
  //
  {
    const R thetaA0 =  pi/3 ;
    const R thetaA1 = -0.33 ;
    const R thetaA2 =  pi/2 ;
    const R thetaA3 = -pi/7 ;
    const R thetaA4 = -pi/5 ;
    const R thetaA5 =  pi/9 ;
    f3c::qgates::RotationTFXY< T >  TFRxyA( thetaA0 , thetaA1 , thetaA2 ,
                                            thetaA3 , thetaA4 , thetaA5 ) ;

    const R thetaB0 = -0.17 ;
    const R thetaB1 =  1.05 ;
    const R thetaB2 =  0.77 ;
    const R thetaB3 =  0.64 ;
    const R thetaB4 = -1.25 ;
    const R thetaB5 = -0.89 ;
    f3c::qgates::RotationTFXY< T >  TFRxyB( thetaB0 , thetaB1 , thetaB2 ,
                                            thetaB3 , thetaB4 , thetaB5 ) ;

    const auto mA = TFRxyA.matrix() ;
    const auto mB = TFRxyB.matrix() ;
    const auto mC = mB * mA ;

    // operator *=
    TFRxyA *= TFRxyB ;

    const auto mAnew = TFRxyA.matrix() ;
    EXPECT_NEAR( std::real( mAnew(0,0) ) , std::real( mC(0,0) ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( mAnew(0,0) ) , std::imag( mC(0,0) ) , 10*eps ) ;
    EXPECT_NEAR( std::real( mAnew(1,1) ) , std::real( mC(1,1) ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( mAnew(1,1) ) , std::imag( mC(1,1) ) , 10*eps ) ;
    EXPECT_NEAR( std::real( mAnew(2,1) ) , std::real( mC(2,1) ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( mAnew(2,1) ) , std::imag( mC(2,1) ) , 10*eps ) ;
    EXPECT_NEAR( std::real( mAnew(3,0) ) , std::real( mC(3,0) ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( mAnew(3,0) ) , std::imag( mC(3,0) ) , 10*eps ) ;

    auto [ thB0 , thB1 , thB2 , thB3 , thB4 , thB5 ] = TFRxyB.thetas() ;
    EXPECT_NEAR( thB0 , thetaB0 , 10*eps ) ;  // thetaB0
    EXPECT_NEAR( thB1 , thetaB1 , 10*eps ) ;  // thetaB1
    EXPECT_NEAR( thB2 , thetaB2 , 10*eps ) ;  // thetaB2
    EXPECT_NEAR( thB3 , thetaB3 , 10*eps ) ;  // thetaB3
    EXPECT_NEAR( thB4 , thetaB4 , 10*eps ) ;  // thetaB4
    EXPECT_NEAR( thB5 , thetaB5 , 10*eps ) ;  // thetaB5
  }

  {
    const R thetaA0 =  pi/3 ;
    const R thetaA1 = -0.33 ;
    const R thetaA2 =  pi/2 ;
    const R thetaA3 = -pi/7 ;
    const R thetaA4 = -pi/5 ;
    const R thetaA5 =  pi/9 ;
    f3c::qgates::RotationTFXY< T >  TFRxyA( thetaA0 , thetaA1 , thetaA2 ,
                                            thetaA3 , thetaA4 , thetaA5 ) ;

    const R thetaB0 = -0.17 ;
    const R thetaB1 =  1.05 ;
    const R thetaB2 =  0.77 ;
    const R thetaB3 =  0.64 ;
    const R thetaB4 = -1.25 ;
    const R thetaB5 = -0.89 ;
    f3c::qgates::RotationTFXY< T >  TFRxyB( thetaB0 , thetaB1 , thetaB2 ,
                                            thetaB3 , thetaB4 , thetaB5 ) ;

    const auto mA = TFRxyA.matrix() ;
    const auto mB = TFRxyB.matrix() ;
    const auto mC = mB * mA ;

    // operator *
    f3c::qgates::RotationTFXY< T > TFRxyC = TFRxyA * TFRxyB ;

    const auto mCnew = TFRxyC.matrix() ;
    EXPECT_NEAR( std::real( mCnew(0,0) ) , std::real( mC(0,0) ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( mCnew(0,0) ) , std::imag( mC(0,0) ) , 10*eps ) ;
    EXPECT_NEAR( std::real( mCnew(1,1) ) , std::real( mC(1,1) ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( mCnew(1,1) ) , std::imag( mC(1,1) ) , 10*eps ) ;
    EXPECT_NEAR( std::real( mCnew(2,1) ) , std::real( mC(2,1) ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( mCnew(2,1) ) , std::imag( mC(2,1) ) , 10*eps ) ;
    EXPECT_NEAR( std::real( mCnew(3,0) ) , std::real( mC(3,0) ) , 10*eps ) ;
    EXPECT_NEAR( std::imag( mCnew(3,0) ) , std::imag( mC(3,0) ) , 10*eps ) ;

    auto [ thA0 , thA1 , thA2 , thA3 , thA4 , thA5 ] = TFRxyA.thetas() ;
    EXPECT_NEAR( thA0 , thetaA0 , 10*eps ) ;  // thetaA0
    EXPECT_NEAR( thA1 , thetaA1 , 10*eps ) ;  // thetaA1
    EXPECT_NEAR( thA2 , thetaA2 , 10*eps ) ;  // thetaA2
    EXPECT_NEAR( thA3 , thetaA3 , 10*eps ) ;  // thetaA3
    EXPECT_NEAR( thA4 , thetaA4 , 10*eps ) ;  // thetaA4
    EXPECT_NEAR( thA5 , thetaA5 , 10*eps ) ;  // thetaA5

    auto [ thB0 , thB1 , thB2 , thB3 , thB4 , thB5 ] = TFRxyB.thetas() ;
    EXPECT_NEAR( thB0 , thetaB0 , 10*eps ) ;  // thetaB0
    EXPECT_NEAR( thB1 , thetaB1 , 10*eps ) ;  // thetaB1
    EXPECT_NEAR( thB2 , thetaB2 , 10*eps ) ;  // thetaB2
    EXPECT_NEAR( thB3 , thetaB3 , 10*eps ) ;  // thetaB3
    EXPECT_NEAR( thB4 , thetaB4 , 10*eps ) ;  // thetaB4
    EXPECT_NEAR( thB5 , thetaB5 , 10*eps ) ;  // thetaB5
  }

}


/*
 * complex float
 */
TEST( f3c_qgates_RotationTFXY , complex_float ) {
  test_f3c_qgates_RotationTFXY< std::complex< float > >() ;
}

/*
 * complex double
 */
TEST( f3c_qgates_RotationTFXY , complex_double ) {
  test_f3c_qgates_RotationTFXY< std::complex< double > >() ;
}

