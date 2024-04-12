import React, { useRef, useState, useEffect } from "react";
import * as d3 from "d3";
import "./App.css";

const App = () => {
    const svgRef = useRef<SVGSVGElement | null>(null);
    const [points, setPoints] = useState<[number, number][]>([]);
    const [delaunay, setDelaunay] = useState<d3.Delaunay<
        [number, number]
    > | null>(null);
    const [voronoi, setVoronoi] = useState<d3.Voronoi<[number, number]> | null>(
        null
    );

    const updateVisualization = (
        newPoints: [number, number][],
        newDelaunay: d3.Delaunay<[number, number]> | null,
        newVoronoi: d3.Voronoi<[number, number]> | null
    ) => {
        const svg = d3.select(svgRef.current);
        svg.selectAll("*").remove();

        svg.append("g")
            .attr("class", "points")
            .selectAll("circle")
            .data(newPoints)
            .enter()
            .append("circle")
            .attr("cx", (d) => d[0])
            .attr("cy", (d) => d[1])
            .attr("r", 3);

        if (newDelaunay) {
            svg.append("g")
                .attr("class", "triangulation")
                .selectAll("path")
                .data(newDelaunay.trianglePolygons())
                .enter()
                .append("path")
                .attr("d", (d) => `M${d.join("L")}Z`)
                .style("stroke", "red")
                .style("stroke-width", 1)
                .style("fill", "none");
        }

        if (newVoronoi) {
            svg.append("g")
                .attr("class", "voronoi")
                .selectAll("path")
                .data(newVoronoi.cellPolygons())
                .enter()
                .append("path")
                .attr("d", (d) => `M${d.join("L")}Z`)
                .style("stroke", "blue")
                .style("stroke-width", 1)
                .style("fill", "none");
        }
    };

    useEffect(() => {
        const svg = d3.select(svgRef.current);

        const handleMouseClick = (event: MouseEvent) => {
            const point = d3.pointer(event, svg.node() as SVGSVGElement);
            setPoints((prevPoints) => [...prevPoints, point]);
        };

        svg.on("click", handleMouseClick);

        return () => {
            svg.on("click", null);
        };
    }, []);

    useEffect(() => {
        const newDelaunay = d3.Delaunay.from(points);
        const newVoronoi = newDelaunay.voronoi();
        updateVisualization(points, newDelaunay, newVoronoi);
        setDelaunay(newDelaunay);
        setVoronoi(newVoronoi);
    }, [points]);

    const clearSvg = () => {
        const svg = d3.select(svgRef.current);
        svg.selectAll("*").remove();
        setPoints([]);
    };

    return (
        <div className="Wrapper">
            <div className="MainArea"></div>
            <h1>Triangulation</h1>
            <svg className="Svg" ref={svgRef} />

            <div className="Menu">
                <button className="Reset" onClick={clearSvg}>
                    Clear
                </button>
            </div>
        </div>
    );
};

export default App;
