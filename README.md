Metro-Bullet
============

Demo of using the Bullet Physics Engine in a Windows 8 Metro DirectX 11 app.

Email queries to gary@taumuon.co.uk or on this post:
http://taumuon-jabuka.blogspot.co.uk/2012/04/bullet-physics-and-directx-11-on.html

Building bullet:

This was tested with Bullet 2.80 revision 2531

The steps to create the bullet libs were
. Download bullet source, and unzip to e.g. C:\Bullet
. Open and convert the project from under <extracted folder>\Bullet\msvc\vs2010_dx11
. Remove the App_DX11ClothDemo, BulletSoftBody and BulletSoftBodyDX11Solvers projects from the solution
. Add the following preprocessor define to all projects:
  WINAPI_FAMILY=WINAPI_PARTITION_APP
. Add the following preprocessor define to the LinearMath project:
  BT_NO_PROFILE
. Change the use of the C Runtime to be Multi-threaded DLL/Multi-threaded Debug Dll

Change the example project's C++ include path to point to the bullet source, e.g. C:\Bullet\src