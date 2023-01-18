.pragma library

function colorWithAlpha(color, alpha) {
    return Qt.hsla(color.hslHue, color.hslSaturation, color.hslLightness, alpha)
}

const DangerColor = "#FF3B30"
const ErrorColor = "#FF3B30"

const SmallLabelWeight = 200
const SmallLabelSize = 11

const PopupX = 20
const PopupTop = 40
const PopupBottom = 20

const PageHeaderHeight = 52
const PageHeaderTitleSize = 28
const PageHeaderTitleWeight = 800
const PageHeaderLeftMargin = 12
const PageHeaderRightMargin = 12

const ToolBarHeight = 32
const ToolBarSeparatorWidth = 2

const ToolButtonSize = 32
const ToolButtonPadding = 4
const ToolButtonCheckedRadius = 4

const ContentLeftMargin = 16
const ContentRightMargin = 16

const ConfigItemHeight = 28
const ConfigGroupTitleHeight = 48
const ConfigGroupTitleBottomMargin = 8
const ConfigGroupTitleFontWeight = 200

const DialogRadius = 12
const DialogPadding = 20
const DialogButtonsHeight = 40

const SplitViewSize = 1
const SplitViewHitAreaPadding = 4

const PopupContentBottomPadding = 12
const PopupItemTopMargin = 8
const PopupItemBottomMargin = 8
