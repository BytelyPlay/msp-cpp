module;

export module TeleportFlags;

// bitmask
export enum TeleportFlags : int {
    RELATIVE_X = 0x0001,
    RELATIVE_Y = 0x0002,
    RELATIVE_Z = 0x0004,

    RELATIVE_YAW = 0x0008,
    RELATIVE_PITCH = 0x0010,

    RELATIVE_VELOCITY_X = 0x0020,
    RELATIVE_VELOCITY_Y = 0x0040,
    RELATIVE_VELOCITY_Z = 0x0080,

    ROTATE_VELOCITY_BEFORE_APPLICATION = 0x0100
};
