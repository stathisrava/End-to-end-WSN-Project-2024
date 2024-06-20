/*import logo from './logo.svg';
import './App.css';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.js</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
      </header>
    </div>
  );
}

export default App; */
// src/App.js

import React, { useEffect, useState } from 'react';
import axios from 'axios';
import './App.css';


function App() {
  const [sensorData, setSensorData] = useState([]);

  useEffect(() => {
    const fetchData = async () => {
      const result = await axios.get('http://localhost:3000/api/sensor-data');
      setSensorData(result.data);
    };

    fetchData();
  }, []);

  return (
  <div className="App grid-pattern">
    <div className="App">
      <h1>Real-time Sensor Data Dashboard</h1>
      
  
     <iframe 
          src="https://charts.mongodb.com/charts-project-0-twifa/public/dashboards/64d115da-b6b0-4bc2-889b-9a24999917d8"
          width="1600" 
          height="700">
          title="MongoDB Charts Dashboard" // Add a descriptive title here
      </iframe> 
  
  
     
    </div>
   </div>
  );
}

export default App;
