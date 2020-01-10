#include <web_view.hpp>

WebView::WebView(unsigned int width, unsigned int height) {
  m_texture = std::make_unique<gl::Texture2d>();
  resize(width, height);

  CefWindowInfo window_info;
  window_info.SetAsWindowless(0);
  CefBrowserSettings browser_settings;
  browser_settings.web_security = STATE_DISABLED;
  browser_settings.windowless_frame_rate = 60;
  CefBrowserHost::CreateBrowserSync(window_info, this, "https://www.nhl.com/", browser_settings, nullptr);
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
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, (unsigned char*)buffer);
  gl::Texture2d::unbind(GL_TEXTURE_2D);
}

void WebView::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
  CefQuitMessageLoop();
}

void WebView::resize(unsigned int width, unsigned int height) {
  m_width = width;
  m_height = height;

  // re-create texture in correct size
  m_texture->bind();
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  gl::Texture2d::unbind(GL_TEXTURE_2D);
}

void WebView::bind_texture() const {
  m_texture->bind();
}
