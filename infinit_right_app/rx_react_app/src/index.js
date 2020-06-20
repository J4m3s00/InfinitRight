import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';
import { ServerConnection } from './server_connection';

ServerConnection.setupConnect();

ReactDOM.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
  document.getElementById('root')
);