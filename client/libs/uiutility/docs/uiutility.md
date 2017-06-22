<!--
Created by Qibin Chen on 20/06/2017.
-->

Documentation - UiUtility
================

![](uiutility_class_diagram.png)

#### WidgetSize

*   Size Definitions of some frequently used ui components can be found here.  

#### ClickableLabel

*   Label that is clickable.

#### PhotoLabel

*   Label that displays a photo and clickable.

##### protected:

*   mouseEvents
    *   ```c++
        virtual void mousePressEvent(QMouseEvent* event) override;
    
        virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
        ```
    
##### public:
*   PhotoLabel
    *   ```c++
        PhotoLabel(int photoID, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
        ```

##### signals:

*   clicked
    *   ```c++
        void clicked(int id);
        
        void rightClicked(int id);
        
        void doubleClicked(int id);
        ```
        
