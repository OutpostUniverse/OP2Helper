# OP2Helper

The OP2Helper library is used to ease development of Outpost 2 missions. It does this by wrapping the Outpost2DLL library, and builds functionality on top of the exported methods. While the Outpost2DLL library is aimed at providing the raw exports from Outpost2.exe (and only the raw exports), the OP2Helper library contains custom code to build functionality around the exported methods.

The OP2Helper library is intentionally simple, in that it depends only the on exported methods from Outpost2DLL, ensuring code stays safe and portable. In particular, this library does not attempt any memory hacking to reach into the game and manipulate parts that are not exported. See [HFL](https://github.com/OutpostUniverse/HFL) and [OP2Internal](https://github.com/OutpostUniverse/OP2Internal) for more advanced memory hacking needs.

A few things the OP2Helper library helps with:
 * Creating base layouts (as data)
 * Creating initial colony conditions (as data)
 * Changing bases and starting conditions based on difficulty settings
 * Randomizing base locations and layouts
 * Randomizing arbitrary lists
 * Classifying units by colony type, building/vehicle, weapon, etc.
 * Bulldozing sections of terrain
 * Setting lava flow areas
 * Setting volcanic eruption animations
 * Simplify in-game messages
 * Enumeration for sounds and voice messages
 * Enumeration for technology ID values
 * Standardized victory/failure conditions
 * Simplify `LOCATION` and `MAP_RECT` manipulation

# Usage

The OP2Helper library is included as part of the [Mission SDK](https://github.com/OutpostUniverse/OP2MissionSDK) project. The Mission SDK project is used by the [LevelTemplate](https://github.com/OutpostUniverse/LevelTemplate) project. Most people will want to start with the LevelTemplate project, which is already configured to use the Mission SDK, and hence also the OP2Helper library.
