import dash
from dash import dcc, html
from dash.dependencies import Input, Output, State
import plotly.graph_objs as go
import requests
from datetime import datetime
import pytz

# Constants for IP and port
IP_ADDRESS = "4.228.61.236"
PORT_STH = 8666
DASH_HOST = "0.0.0.0"

# Function to get luminosity data from the API
def get_luminosity_data(lastN):
    url = f"http://{IP_ADDRESS}:{PORT_STH}/STH/v1/contextEntities/type/Sensor/id/urn:ngsi-ld:devin/attributes/luminosity?lastN={lastN}"
    headers = {
        'fiware-service': 'smart',
        'fiware-servicepath': '/'
    }
    response = requests.get(url, headers=headers)
    if response.status_code == 200:
        data = response.json()
        try:
            values = data['contextResponses'][0]['contextElement']['attributes'][0]['values']
            return values
        except KeyError as e:
            print(f"Key error: {e}")
            return []
    else:
        print(f"Error accessing {url}: {response.status_code}")
        return []

# Function to convert UTC timestamps to Brazil time
def convert_to_brazil_time(timestamps):
    utc = pytz.utc
    brazil = pytz.timezone('America/Sao_Paulo')
    converted_timestamps = []
    for timestamp in timestamps:
        try:
            timestamp = timestamp.replace('T', ' ').replace('Z', '')
            converted_time = utc.localize(datetime.strptime(timestamp, '%Y-%m-%d %H:%M:%S.%f')).astimezone(brazil)
        except ValueError:
            converted_time = utc.localize(datetime.strptime(timestamp, '%Y-%m-%d %H:%M:%S')).astimezone(brazil)
        converted_timestamps.append(converted_time)
    return converted_timestamps

# Set lastN value
lastN = 10  # Get 10 most recent points at each interval

app = dash.Dash(__name__)

app.layout = html.Div([
    html.H1('Luminosity Data Viewer'),
    dcc.Graph(id='luminosity-graph'),
    dcc.Store(id='luminosity-data-store', data={'timestamps': [], 'luminosity_values': []}),
    dcc.Interval(
        id='interval-component',
        interval=10 * 1000,  # in milliseconds (10 seconds)
        n_intervals=0
    )
])

@app.callback(
    Output('luminosity-data-store', 'data'),
    Input('interval-component', 'n_intervals'),
    State('luminosity-data-store', 'data')
)
def update_data_store(n, stored_data):
    # Get luminosity data
    data_luminosity = get_luminosity_data(lastN)

    if data_luminosity:
        # Extract values and timestamps
        luminosity_values = [float(entry['attrValue']) for entry in data_luminosity]
        timestamps = [entry['recvTime'] for entry in data_luminosity]

        # Convert timestamps to Brazil time
        timestamps = convert_to_brazil_time(timestamps)

        # Replace the stored data with the new data
        stored_data = {
            'timestamps': timestamps,
            'luminosity_values': luminosity_values,
        }

        return stored_data

    return stored_data

@app.callback(
    Output('luminosity-graph', 'figure'),
    Input('luminosity-data-store', 'data')
)
def update_graph(stored_data):
    if stored_data['timestamps']:
        # Luminosity plot
        trace_luminosity = go.Scatter(
            x=stored_data['timestamps'],
            y=stored_data['luminosity_values'],
            mode='lines+markers',
            name='Luminosity',
            line=dict(color='orange')
        )

        # Create figure with the luminosity trace
        fig = go.Figure(data=[trace_luminosity])
        fig.update_layout(
            title='Luminosity Over Time',
            xaxis_title='Timestamp',
            yaxis_title='Luminosity (units)',
            legend=dict(title='Legend'),
            hovermode='closest'
        )

        return fig

    return {}

if __name__ == '__main__':
    app.run_server(debug=True, host=DASH_HOST, port=8050)
