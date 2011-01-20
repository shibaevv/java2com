package com.argus.activex;

import java.awt.Canvas;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Rectangle;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;

/**
 * See http://www.codeproject.com/java/javacom.asp
 * Class to get the HWND of a Java Heavy Weight component.
 */
public class ActiveXCanvas extends Canvas
    implements ComponentListener
{
    /**
     * 
     */
    private static final long serialVersionUID = -3135422862963355114L;
    //
    private int m_hWnd;
    //
    private Dispatch m_dispatch;
    private Class m_dispatchClass;

    public ActiveXCanvas(Class dispatchClass)
    {
        this.m_dispatchClass = dispatchClass;
        addComponentListener(this);
    }

//    public synchronized native void ResizeCanvas(int hwnd);

    public void addNotify()
    {
        super.addNotify();
        
        // get the HWND of a Java Heavy Weight component.
        m_hWnd = DispatchUtils.getHWND(this);
        try {
            // create activex in java canvas
            m_dispatch = (Dispatch) m_dispatchClass
                .getConstructor(new Class [] {Component.class})
                .newInstance(new Object [] {this});
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void componentHidden(ComponentEvent e)
    {
    }

    public void componentMoved(ComponentEvent e)
    {
    }

    public void componentResized(ComponentEvent e)
    {
//        ResizeCanvas(hWnd);
    }

    public void componentShown(ComponentEvent e)
    {
    }

    public Dispatch getDispatch() {
        return m_dispatch;
    }

    // entry point for resizing
    private void resizeControl(int width, int height)
    {
        if (m_hWnd != 0)
            DispatchUtils.resizeControl(m_hWnd, width, height);
    }

    public void setSize(int width, int height) 
    {
        super.setSize(width,height);
        resizeControl(width, height);
    }

    public void setSize(Dimension d) 
    {
        super.setSize(d);
        resizeControl(d.width, d.height);
    }

    public void setBounds(int x, int y, int width, int height) 
    {
        super.setBounds(x,y,width,height);
        resizeControl(width, height);
    }

    public void setBounds(Rectangle r) 
    {
        super.setBounds(r);
        resizeControl(r.width, r.height);
    }

}