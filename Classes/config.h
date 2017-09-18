#ifndef config_h
#define config_h


// 属性情報を列挙型で指定
enum ELEMENTS {
    TYPE_FIRE,// 火
    TYPE_WATER,// 水
    TYPE_WIND,// 風
    TYPE_EARTH,// 地
    TYPE_LIGHT,// 光
    TYPE_DARK// 闇
};

// コマンド情報を列挙型で指定
enum COMMANDS {
    TYPE_WEAPON,// 武器攻撃
    TYPE_JUMP,// ジャンプ
    TYPE_MAGIC// 魔法攻撃
};

#endif /* config_h */
