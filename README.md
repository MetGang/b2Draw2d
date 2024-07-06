# b2Draw2d

box2d is C++ library - known as box2d v2.x

Collection of graphical frontends for [box2d](https://github.com/erincatto/box2d) debug rendering.

## Supported frontends

* [raylib](https://github.com/raysan5/raylib)
* [SFML](https://github.com/SFML/SFML)

## Scaling

To ensure best precision box2d uses units called *meters* which is just a fancy name for small floats because floating-point numbers lose precision when the number gets bigger. That's why it's the best to keep size of your physics object in range from 0.0f to 10.0f and then use scale while rendering.

## License

MIT, see [license](LICENSE) for more information.
