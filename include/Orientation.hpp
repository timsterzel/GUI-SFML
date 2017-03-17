#pragma once
#ifndef ORIENTATION_HPP
#define ORIENTATION_HPP

namespace gsf
{
    enum Orientation
    {
        None = 0,
        Center = 1 << 1,
        CenterHorizontal = 1 << 2,
        CenterVertical = 1 << 3,
        Left = 1 << 4,
        Right = 1 << 5,
        Top = 1 << 6,
        Bottom = 1 << 7
    };
}

#endif // ORIENTATION_HPP
