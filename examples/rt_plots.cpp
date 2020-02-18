#include <mahi/gui.hpp>

using namespace mahi::gui;

class RealTimePlotDemo : public Application {
public:
    RealTimePlotDemo() : Application(800,500,"Real Time Plot Demo") { 
        ImGui::DisableViewports();
        items1.resize(1);
        plot1.xAxis.maximum = 10;
        plot1.xAxis.lockMin = true;  plot1.xAxis.lockMax = true;
        items2.resize(3);
        plot2.xAxis.maximum = 10;
        plot2.xAxis.lockMin = true;  plot2.xAxis.lockMax = true;
    }

    void update() override {
        auto [w,h] = getWindowSize();
        ImGui::BeginFixed("Real Time Plots", {0,0}, ImVec2(w,h), ImGuiWindowFlags_NoTitleBar);  
        float regionHeight = ImGui::GetContentRegionAvail().y;   
        auto [x,y] = getMousePosition();
        // rolling plot example
        ImGui::PlotItemRollPoint(items1[0], (float)time(), + x*0.0005f + Random::range(0.49f,0.51f), 10.0f);
        ImGui::Plot("My Rolling Plot", plot1, items1, ImVec2(-1,regionHeight/2));
        // buffering plot example
        ImGui::PlotItemBufferPoint(items2[0], (float)time(), x*0.0005f + Random::range(0.49f,0.51f), 1000);
        ImGui::PlotItemBufferPoint(items2[1], (float)time(), y*0.0005f + Random::range(0.49f,0.51f), 1000);
        ImGui::PlotItemBufferPoint(items2[2], (float)time(), (x+y)*0.00025f + Random::range(0.49f,0.51f), 1000);

        plot2.xAxis.minimum = (float)time() - 10;
        plot2.xAxis.maximum = (float)time();
        ImGui::Plot("My Buffering Plot", plot2, items2, ImVec2(-1,-1));
        ImGui::End();
    }

    ImGui::PlotInterface plot1, plot2;
    std::vector<ImGui::PlotItem> items1, items2;
};

int main(int argc, char const *argv[])
{
    RealTimePlotDemo demo;
    demo.run();
    return 0;
}