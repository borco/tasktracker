pragma Singleton
import QtQuick

QtObject {

    function colorWithAlpha(color, alpha) {
        return Qt.hsla(color.hslHue, color.hslSaturation, color.hslLightness, alpha)
    }

    readonly property string dangerColor: "#FF3B30"
    readonly property string errorColor: "#FF3B30"

   readonly property int smallLabelWeight: 200
   readonly property int smallLabelSize: 11

   readonly property int xSmallLabelWeight: 200
   readonly property int xSmallLabelSize: 9

   readonly property int popupX: 20
   readonly property int popupTop: 40
   readonly property int popupBottom: 20

   readonly property int pageHeaderHeight: 52
   readonly property int pageHeaderTitleSize: 28
   readonly property int pageHeaderTitleWeight: 800
   readonly property int pageHeaderLeftMargin: 12
   readonly property int pageHeaderRightMargin: 12
   readonly property int pageHeaderSpacing: 12

   readonly property int toolBarHeight: 32
   readonly property int toolBarSeparatorWidth: 2

   readonly property int toolButtonSize: 32
   readonly property int toolButtonPadding: 4
   readonly property int toolButtonCheckedRadius: 4

   readonly property int contentLeftMargin: 16
   readonly property int contentRightMargin: 16

   readonly property int configItemHeight: 28
   readonly property int configGroupTitleHeight: 48
   readonly property int configGroupTitleBottomMargin: 8
   readonly property int configGroupTitleFontWeight: 200

   readonly property int dialogRadius: 12
   readonly property int dialogPadding: 20
   readonly property int dialogButtonsHeight: 40

   readonly property int splitViewSize: 3
   readonly property int splitViewHitAreaPadding: 4

   readonly property int popupContentBottomPadding: 12
   readonly property int popupItemTopMargin: 8
   readonly property int popupItemBottomMargin: 8
}
