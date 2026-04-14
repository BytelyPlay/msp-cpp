module;

export module DisplayedSkinParts;

// Should be a bitmask.
export enum DisplayedSkinParts : unsigned char {
    CAPE = 0x01,
    JACKET = 0x02,
    LEFT_SLEEVE = 0x04,
    RIGHT_SLEEVE = 0x08,
    LEFT_PANTS_LEG = 0x10,
    RIGHT_PANTS_LEG = 0x20,
    HAT_ENABLED = 0x40
};
