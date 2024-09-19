import CountryLookup from './CountryLookup';

export default function Footer() {
    return (
        <footer className='absolute bottom-0 text-sm text-gray-50 bg-gray-800 w-full'>
            <div className='px-8 py-3'>
                <CountryLookup />
            </div>
        </footer>
    );
}
