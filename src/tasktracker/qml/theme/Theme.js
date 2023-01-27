.pragma library

function colorWithAlpha(color, alpha) {
    return Qt.hsla(color.hslHue, color.hslSaturation, color.hslLightness, alpha)
}

// https://developer.apple.com/design/human-interface-guidelines/foundations/color/#specifications

const LightRed = "#FF3B30"
const LightOrange = "#FF9500"
const LightYellow = "#FFCC00"
const LightGreen = "#34C759"
const LightMint = "#00C7BE"
const LightTeal = "#30B0C7"
const LightCyan = "#32ADE6"
const LightBlue = "#007AFF"
const LightIndigo = "#5856D6"
const LightPurple = "#AF52DE"
const LightPink = "#FF2D55"
const LightBrown = "#A2845E"

const LightGray1 = "#8E8E93"
const LightGray2 = "#AEAEB2"
const LightGray3 = "#C7C7CC"
const LightGray4 = "#D1D1D6"
const LightGray5 = "#E5E5EA"
const LightGray6 = "#F2F2F7"

const DangerColor = LightRed
const ErrorColor = LightRed

const SmallLabelWeight = 200
const SmallLabelSize = 11

const XSmallLabelWeight = 200
const XSmallLabelSize = 9

const PopupX = 20
const PopupTop = 40
const PopupBottom = 20

const PageHeaderHeight = 52
const PageHeaderTitleSize = 28
const PageHeaderTitleWeight = 800
const PageHeaderLeftMargin = 12
const PageHeaderRightMargin = 12
const PageHeaderSpacing = 12

const ToolBarHeight = 32
const ToolBarSeparatorWidth = 2

const ToolButtonSize = 32
const ToolButtonPadding = 4
const ToolButtonCheckedRadius = 4

const ContentTopMargin = 12
const ContentLeftMargin = 16
const ContentRightMargin = 16

const ConfigItemHeight = 28

const GroupTitleHeight = 48
const GroupTitleBottomMargin = 8
const GroupTitleFontWeight = 200

const DialogRadius = 12
const DialogPadding = 20
const DialogButtonsHeight = 40

const SplitViewSize = 3
const SplitViewHitAreaPadding = 4

const PopupContentBottomPadding = 12
const PopupItemTopMargin = 8
const PopupItemBottomMargin = 8

const RoundLabelDiameter = 30
const RoundLabelBorderWidth = 2
