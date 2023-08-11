// Safely connect functions to signals, and also print the object name on signal
// use it like this inside of WindowUI, capturing class instance reference in lambda:
// safe_connect_signal(widget, widget->signal_something(), [this](...){...});
template <typename WidgetClass, typename SignalType, typename Function>
void
safe_connect_signal(WidgetClass *widget, SignalType signal, const Function &call_function) {
    if (widget) {
        signal.connect([call_function](auto&&... args) {
            call_function(std::forward<decltype(args)>(args)...);
        });
    }
}

// Alternate version for signal_response() or whenever response_id is necessary, used like this:
// safe_connect_signal(widget, widget->signal_something(), [this](int response_id, Gtk::SomeWidget* something){...});
template <typename WidgetClass, typename SignalType, typename Function>
void
safe_connect_signal_rid(WidgetClass *widget, SignalType signal, const Function &call_function) {
    if (widget) {
        const Glib::ustring content = widget->get_name();
        signal.connect([content, call_function, widget](int response_id) {
            call_function(response_id, widget);
        });
    }
}
