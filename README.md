Metro-Bullet
============

Demo of using the Bullet Physics Engine in a Windows Store DirectX 11 app.

Email queries to gary@taumuon.co.uk or on this post:
http://taumuon-jabuka.blogspot.co.uk/2012/04/bullet-physics-and-directx-11-on.html

Building bullet:

This was tested with Bullet 2.81 revision 2613

The steps to create the bullet libs were
. Download bullet source, and unzip to e.g. C:\Bullet
. Open and convert the solution from under build\vs2010
. Remove projects except: BulletCollision, BulletDynamics, LinearMath
. Add the following preprocessor defines to all projects:
  WINAPI_FAMILY=WINAPI_PARTITION_APP
  BT_NO_PROFILE
. Change the use of the C Runtime to be Multi-threaded DLL/Multi-threaded Debug Dll

Change the MetroBullet project's C++ include path to point to the bullet source, e.g. C:\Bullet\src