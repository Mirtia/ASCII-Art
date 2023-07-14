# ASCII art

## Notes

To use freetype you have to download the following libraries. I used *vcpkg*.

```bash
# VCPKG_DEFAULT_TRIPLET
vckpg install harfbuzz 
vckpg install freetype
```

Then, when configuring the build files you have to enable ```WITH_FREETYPE``` option. I also had to modify the ```CMakeList.txt```  in OpenCV contributions [```/modules/freetype/CMakeLists.txt```](https://gist.github.com/UnaNancyOwen/14c72a3f10a46d41c359ab6ea307a1d2) to make it work.
