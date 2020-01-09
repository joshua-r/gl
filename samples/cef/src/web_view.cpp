#include <web_view.hpp>

WebView::WebView() {
  m_texture = std::make_unique<gl::Texture2d>();
}

CefRefPtr<CefLifeSpanHandler> WebView::GetLifeSpanHandler() {
  return this;
}

CefRefPtr<CefRenderHandler> WebView::GetRenderHandler() {
  return this;
}

void WebView::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) {
  rect = CefRect(0, 0, m_width, m_height);
}

void WebView::OnPaint(CefRefPtr<CefBrowser> browser,
                      PaintElementType type,
                      const RectList& dirtyRects,
                      const void* buffer,
                      int width,
                      int height) {
  m_texture->bind();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (unsigned char*)buffer);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  gl::Texture2d::unbind(GL_TEXTURE_2D);
}

void WebView::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  CefQuitMessageLoop();
}

void WebView::bind_texture() const {
  m_texture->bind();
}
